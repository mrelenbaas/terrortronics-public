# %BANNER_BEGIN%
# ---------------------------------------------------------------------
# %COPYRIGHT_BEGIN%
# Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
# Use of this file is governed by the Software License Agreement,
# located here: https://www.magicleap.com/software-license-agreement-ml2
# Terms and conditions applicable to third-party materials accompanying
# this distribution may also be found in the top-level NOTICE file
# appearing herein.
# %COPYRIGHT_END%
# ---------------------------------------------------------------------
# %BANNER_END%

import pickle
from pickle import PickleError

import build_vars
from vswhere import *

def mkdir_p(path):
    try:
        if not path or os.path.isdir(path):
            return False
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        import errno
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise
    return True


def rename_with_retry(src, dest):
    """
    Rename 'src' to 'dest', allowing for other parallel
    processes that may be attempting the same.
    :param src:
    :param dest:
    """

    if src == dest:
        return

    # now, try to get the destination replaced
    # atomically
    last_error = None
    tries = 0
    while tries < 8:
        try:
            os.replace(src, dest)
            # good, got it done
            return
        except PermissionError as e:
            # we only get here on Windows
            # (in POSIX, os.rename deletes an existing dest)
            last_error = e
            try:
                # be sure we can delete the target
                os.chmod(dest, 0o666)
                os.remove(dest)
                # good, can try renaming again now
            except FileNotFoundError:
                # hmm, nothing was there...
                # maybe we deleted it in a parallel
                # packaging step...?
                tries = 0
            except OSError as e:
                # hmm, something worse happened
                raise
        except OSError as e:
            # hmm, something worse happened
            raise

        tries += 1

    # ran out of tries
    raise last_error

class BuildException(Exception):
    def __init__(self, message, *args, build_args=None, **kwargs):
        if build_args:
            msg = message + "\ncommand line: " + ' '.join(build_args)
        else:
            msg = message
        if args:
            msg += " (" + (" ".join([str(arg) for arg in args])) + ")"
        Exception.__init__(self, msg, **kwargs)

class VsEnv:
    """
    Small class to encapsulte env vars and be (de-)serialized.
    """
    def __init__(self, common_tools_path):
        self.vcvars_path = common_tools_path
        self.env = {}

    # Keep these variables even if they were set before invoking vcvarsall/vsdevcmd
    _reqd_vars = [
        'INCLUDE',
        'LIB',
        'PATH',
        'UCRTCONTENTROOT'
        'UCRTVERSION',
        'UNIVERALCRTSKDIR',
        'VCINSTALLDIR',
        'VCTARGETSPATH',
        'WINDOWSLIBPATH',
        'WINDOWSDKDIR',
        'WINDOWSDKLIBVERSION',
        'WINDOWSDKVERSION',
    ]

    def process_vsdevcmd_output(self, full_env):
        # get diffs from current env (don't apply unrelated env vars from an older detection)
        # and keep uppercase version of PATH to simplify logic below
        def canon_env(k):
            if k.upper() == 'PATH':
                return 'PATH'
            return k

        self.env = {canon_env(k): v for (k, v) in full_env.items() if k.upper() in self._reqd_vars or os.environ.get(k, None) != v}

        # PATH is a special case: add the new prepended/appended settings to get those related to MSVC setup,
        # but don't embed the current PATH there
        my_path = os.environ.get('PATH', os.environ.get(os.defpath))  # OS variable may be either case
        vs_path = self.env.get('PATH')  # we normalized this above
        if my_path is None or vs_path is None:
            # suspicious; don't cache
            print("Cannot detect PATH changes; not caching!")
            return

        try:
            my_index = vs_path.index(my_path)
        except IndexError:
            # suspicious; don't cache
            print("MSVC setup script modified PATH in an unexpected way; not caching!")
            return

        # save a pattern that preserves the prepended and appended entries
        path_update_pattern = vs_path[0:my_index] + "{PATH}" + vs_path[my_index + len(my_path):]
        self._update_path(path_update_pattern)


    def _update_path(self, vs_cached_path):
        # we normalize PATH to full uppercase and add this marker below
        path_pattern = vs_cached_path or '{PATH}'
        temp_path = path_pattern.replace('{PATH}', os.getenv('PATH', ''))
        self.env['PATH'] = self._cleanup_path(temp_path)


    def _cleanup_path(self, temp_path):
        # now reduce duplicate entries to avoid the dreaded 4k limit
        seen_paths = set()
        new_paths = []
        for path in temp_path.split(os.pathsep):
            # strip trailing slash (really, MSVC?  Like to waste space and cause trouble?)
            if path and path[-1] in ['/', '\\']:
                path = path[:-1]


            unnecessary_path_elems = ["TestWindow", "TeamFoundation", "Team Tools", "VSPerfCollectionTools", "SQL Server", "Cloud SDK", "python27", "Compute Engine", "Conan", "Notepad++"]
            # strip out unnecessary MSVC, Python, and other random paths to reduce leading spam
            if any(elem in path for elem in unnecessary_path_elems):
                continue

            lower_path = path.lower()
            if not lower_path in seen_paths:
                seen_paths.add(lower_path)
                new_paths.append(path)

        # just in case...
        new_paths.append(os.path.join(os.getenv('SystemRoot'), "system32"))
        new_path = os.pathsep.join(new_paths)
        return new_path


class VsEnvCache:
    """
    To easily build for MSVC, we need VS env vars to be set,
    but starting the Visual Studio command prompt or running
    vcvarsall is soooooo sloooooow.  So this caches the data
    from that, requiring only one unbearably long pause when
    updating Visual Studio command line tools.
    """
    def __init__(self, toolinfo):
        self._family = toolinfo.product_line_version
        self._version = toolinfo.version_major

        self._tool_search_path = {}
        self._system_libs_paths = {}
        self._system_include_paths = {}

        self._current_tool_search_path = None
        self._current_system_lib_paths = None
        self._current_system_include_paths = None

        self._tools = {}
        self._vs_env = VsEnv(toolinfo.common_tools_path)


    @staticmethod
    def get_cache_dir():
        return os.path.join(os.environ.get('USERPROFILE', os.environ.get('HOME', '.')), 'AppData', 'Local', 'mlsdk')


    @staticmethod
    def _convert_string_to_dict(input_string):
        return dict([line.split("=", 1) for line in input_string.strip().replace("\r", "").split("\n")])


    def _build_vs_env(self, build_arch, host_arch, force_rescan=False):
        # MSVC scripts are very slow -- remember the likely-to-be-invariant information
        # between runs.  This is optimized for a single installation of 2015 and 2017.
        # The cache of information is used only the detected _vcvars_path,
        # the MSVC version, and the host/target architecture match.

        # see if have a cached copy
        cache_dir = self.get_cache_dir()
        cache_file = os.path.join(cache_dir, "{}_{}_{}.dat".format(self._family, build_arch, host_arch))
        if not force_rescan and os.path.exists(cache_file):
            try:
                with open(cache_file, 'rb') as f:
                    cache_info = pickle.load(f)
                    if isinstance(cache_info, VsEnv) and self._vs_env.vcvars_path == cache_info.vcvars_path:
                        # new env is the last-detected env but with PATH using a pattern
                        cache_info._update_path(cache_info.env.get('PATH'))
                        self._vs_env = cache_info
                        return
            except (OSError, PickleError) as e:
                print("Failed to read cache file: " + str(e))

        # else, do the slow work to scan them
        full_env = self._scan_vs_env(build_arch, host_arch)
        self._vs_env.process_vsdevcmd_output(full_env)
        # and try to save
        try:
            mkdir_p(cache_dir)
            temp_cache_file = cache_file + str(os.getpid())
            with open(temp_cache_file, 'wb') as f:
                pickle.dump(self._vs_env, f)

            rename_with_retry(temp_cache_file, cache_file)
        except OSError as e:
            # nope, just ignore
            print("Failed to write cache file: " + str(e))


    def _scan_vs_env(self, build_arch, host_arch):
        """
        Detect which env vars are required for MSVC builds
        :param build_arch:
        :param host_arch:
        :return: set of all variables detected after invoking VsDevCmd.bat
        """
        cmd = [
            os.path.join(self._vs_env.vcvars_path, "VsDevCmd.bat"),
            "-no_logo",
            "-arch={}".format(build_arch),
            "-host_arch={}".format(host_arch),
            "&",
            "set",
        ]
        comp = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)

        if comp.returncode or comp.stdout.startswith("[ERROR:"):
            raise BuildException("Failed to find VS environment", comp.stdout + comp.stderr, build_args=cmd)
        return self._convert_string_to_dict(comp.stdout)

    def _locate_vc(self, build_arch, host_arch, force_rescan=False):
        """
        Locate the binaries for the toolchain and set the _vs_env
        :param build_arch:
        :param host_arch:
        :param force_rescan:
        :raises BuildException
        """
        tool_arch = "{}_{}".format(build_arch, host_arch)

        self._build_vs_env(build_arch, host_arch, force_rescan=force_rescan)

        for key, value in self._vs_env.env.items():
            # The Visual Studio environment is just an augmentation of the existing system environment at the time
            # the vcvars batch file was called, so it's safe to overwrite the system environment with the new values.
            os.environ[key] = value

        tool_search_path = []
        system_lib_paths = []
        system_include_paths = []

        def split_path_string_into_list(path_string):
            # Canonicalize all paths to be in a Unix-like format.
            return [path.replace("\\", "/") for path in path_string.split(os.pathsep) if path]

        for key, value in os.environ.items():
            key_lowered = key.lower()

            if key_lowered == "path":
                tool_search_path.extend(split_path_string_into_list(value))

            elif key_lowered == "lib":
                system_lib_paths.extend(split_path_string_into_list(value))

            elif key_lowered == "include":
                system_include_paths.extend(split_path_string_into_list(value))

        if not tool_search_path:
            raise BuildException("PATH env not found for toolchain {}".format(self._family))

        self._tool_search_path[tool_arch] = tool_search_path
        self._system_libs_paths[tool_arch] = system_lib_paths
        self._system_include_paths[tool_arch] = system_include_paths

        self._current_tool_search_path = self._tool_search_path[tool_arch]
        self._current_system_lib_paths = self._system_libs_paths[tool_arch]
        self._current_system_include_paths = self._system_include_paths[tool_arch]


    def exists(self):
        return bool(self._vs_env.vcvars_path)

    def _register_tool_based_on_driver(self, var, names):
        for dirp in self._current_tool_search_path:
            for name in names:
                path = os.path.join(dirp, name)
                if os.path.isfile(path):
                    self._tools[var] = path
                    return None
        return "did not find any matches for " + (", ".join(names)) + " in environment"

    def detect(self, force_rescan=False):
        """
        Detect the desired tools in the machine or environment.

        This should populate self._vs_env.

        This method tells whether the receiver is available
        for real builds.
        :rtype: str for error or None for detected
        """
        # Only when building for Windows should we verify that the selected version of Visual Studio is installed.
        if not self.exists():
            return "No Visual Studio installation could be found for toolchain {}".format(self._family)

        # for now, ignore x86
        host_arch = 'x64'
        build_arch = 'x64'

        try:
            self._locate_vc(build_arch, host_arch, force_rescan=force_rescan)
        except BuildException as e:
            return str(e)

        # update full driver path
        err = self._register_tool_based_on_driver(build_vars.CC, ["cl.exe"])
        if err:
            return err

        err = self._register_tool_based_on_driver(build_vars.CXX, ["cl.exe"])
        if err:
            return err

        err = self._register_tool_based_on_driver(build_vars.LD, ["link.exe"])
        if err:
            return err

        err = self._register_tool_based_on_driver(build_vars.AR, ["lib.exe"])
        if err:
            return err

        err = self._register_tool_based_on_driver(build_vars.AS, ["ml{}.exe".format(
            "64" if build_arch == 'x64' else "")])
        if err:
            return err

        err = self._register_tool_based_on_driver(build_vars.RC, ["rc.exe"])
        if err:
            return err

        return None

    def update_env(self, env):
        env.update(self._vs_env.env)

    def tools(self):
        return self._tools
