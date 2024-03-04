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

from __future__ import print_function
import sys
vi = sys.version_info
if (vi.major, vi.minor) < (3, 5):
  print("Please run this script with Python 3.5 or newer")
  sys.exit(1)
import os
import time
import shutil
import platform
import shlex
import subprocess
from subprocess import PIPE
import re
from typing import Optional
RELEASE = 'release'
DEBUG = 'debug'
DEVICE = 'device'
HOST = 'host'
CONFIG_CHOICE = [RELEASE, DEBUG]
TARGETS_CHOICE = [DEVICE, HOST]
CMAKE_VERSION_PATTERN = re.compile("(\d+\.?)+")
is_verbose = False
def print_step(msg, finished=False):
  sys.stdout.flush()
  sys.stderr.flush()
  if finished:
    print('\n')
  print("[{}] >>>>>> {}\n".format(time.strftime("%H:%M:%S"), msg))
  sys.stdout.flush()
  sys.stderr.flush()

def launch(args, **kwargs):
  """ Launch program from @args and return exit code """
  comp = launch_with_completion(args, **kwargs)
  return comp.returncode if comp else -1

def launch_with_completion(args, **kwargs):
  """ Launch program from @args and return ProcessCompletion object """
  if is_verbose:
    cmd_str = shlex.quote(' '.join(args))
    env = kwargs.get('env')
    if env:
      orig_env = dict(os.environ)
      for k, v in env.items():
        if k not in orig_env or orig_env[k] != env[k]:
          cmd_str = k + '=' + v + ' ' + cmd_str
    print("[{}] Running: {}".format(time.strftime("%H:%M:%S"), cmd_str))
    sys.stdout.flush()
    sys.stderr.flush()
  # Workaround for bug affecting CI windows nodes. Sets mabu's PYTHON variable
  # to match the calling python executable. On CI, it seemed to switch to
  # the system default python under some conditions.
  if args[0] == "mabu" or args[0] == "mabu.cmd":
    args.append("PYTHON=" + sys.executable)
  try:
    comp = subprocess.run(args, **kwargs)
    return comp
  except subprocess.TimeoutExpired:
    print(args, "has taken more than", kwargs['timeout'], "seconds and has been terminated")
    return None
  finally:
    sys.stdout.flush()
    sys.stderr.flush()

def find_mlsdk():
  """ find the appropriate MLSDK to use """
  mlsdk = os.getenv('MAGICLEAP_SDK_ROOT')
  if not mlsdk:
    # search PATH to see if it has been set up
    for p in (os.getenv('Path') or os.getenv('PATH')).split(os.pathsep):
      if os.path.exists(os.path.join(p, 'include/ml_api.h')):
        mlsdk = p
        break
  return mlsdk

def update_for_ccache(cmdline, ccache):
  if ccache == 'ccache':
    # default value: make sure it exists
    ccache = shutil.which('ccache')
    if not ccache:
      print("**** Cannot locate ccache, ignoring --ccache")
  if ccache:
    cmdline.insert(0, 'COMPILER_PREFIX=' + ccache)
    cmdline.insert(0, 'LINKER_PREFIX=' + ccache)

def get_os_segment():
  return {
      'Windows': 'win64',
      'Darwin': 'osx',
      'Linux': 'linux64'
  } [platform.system()]

def find_files(d, functor):
  bins = []
  for dirpath, dirnames, filenames in os.walk(d):
    if is_non_cli_binary_path(dirpath):
      # don't recurse
      dirnames[:] = []
      continue
    for file in filenames:
       full = os.path.join(dirpath, file)
       if functor(full):
         bins.append(full)
  return bins
def is_non_cli_binary_path(path):
  """ Detect if directory searches descend into non-CLI tools """
  return 'uifrontend' in path.lower() or 'unity' in path.lower()
def is_elf(path):
  with open(path, 'rb') as f:
    sig = f.read(4)
    return sig == b'\x7fELF'
def is_macho(path):
  with open(path, 'rb') as f:
    sig = f.read(4)
    return sig == b'\xCF\xFA\xED\xFE'
if sys.platform == 'linux':
  def is_executable(path):
    ext = os.path.splitext(path)[1]
    return ext == "" and is_elf(path)
elif sys.platform == 'darwin':
  def is_executable(path):
    ext = os.path.splitext(path)[1]
    return ext == "" and is_macho(path)
else:
  def is_executable(path):
    ext = os.path.splitext(path)[1].lower()
    return ext == '.exe'

def fix_permissions(distdir):
  print_step("Correcting file permissions...")
  exes = find_files(distdir, is_executable)
  for exe in exes:
    if is_verbose:
      print("...", exe)
    os.chmod(exe, 0o777)
  print()

# failure_callback is a function that takes one
# parameter. If this function returns anything but None
# it means that the failure callback has handled the error
# and run will -not- terminate the process, run will then return
# whatever the failure_callback returned.
def run(cmd, verbose=False, do_prints=True, failure_callback=None, custom_env=os.environ):
  if do_prints or verbose:
    print ("cmd: " +  ' '.join(cmd))
  p = None
  try:
    p = subprocess.run(cmd, stderr=PIPE, stdout=PIPE, universal_newlines=True, env=custom_env)
  except (FileNotFoundError, OSError) as err:
    if failure_callback:
      res = failure_callback(err)
      if res is not None:
        return res
    print("Running {} failed with:\n\t{}".format(cmd, err))
    exit(1)
  if verbose or p.returncode != 0:
    print ('{}{}'.format("cmd::resultcode: \n", p.returncode))
    if p.stdout != '':
      print ('{}{}'.format("cmd::stdout: \n", p.stdout))
    if p.stderr != '':
      print ('{}{}'.format("cmd::stderr: \n", p.stderr))
  if p.returncode != 0:
    if failure_callback:
      res = failure_callback(p.returncode)
      if res is not None:
        return res
    exit(p.returncode)
  return (p.returncode, p.stdout, p.stderr)

def get_ninja_path(default_path=None):
  ninja_path = shutil.which("ninja", path=default_path) # search in PATH
  if ninja_path is None:
    ninja_path = shutil.which("ninja", path=get_cmake_path()) # search in cmake's dir
  return ninja_path

def get_cmake_path(target_version_str: str='3.22.1') -> str:
  '''Returns path to cmake newer or equal to the specified version.
  If a version matching target_version_str is available,
  it will be returned. If not, a newer version will be returned or an
  error if none or only older versions are found.
  Args:
      target_version_str (str): Preferred version of cmake in format xxx.xxx.xxx
  '''
  target_version = version_to_int_tuple(target_version_str)
  print("\n\n> Getting cmake path:")
  sdk_root = get_sdk_root()
  used_version_str = None
  result_path = None
  if sdk_root is not None:
    sdk_cmake_path = os.path.join(sdk_root, 'cmake')
    if os.path.exists(sdk_cmake_path):
      cmake_versions = sorted([version_to_int_tuple(f.name) for f in os.scandir(sdk_cmake_path) if f.is_dir() and CMAKE_VERSION_PATTERN.match(f.name)])
      if target_version in cmake_versions:
        result_path = os.path.normpath(os.path.join(sdk_cmake_path, target_version_str, 'bin'))
        used_version_str = target_version_str
      elif cmake_versions and cmake_versions[-1] > target_version:
        used_version_str = '.'.join(map(str, cmake_versions[-1]))
        print("> WARN: Using newer version of cmake ({}), than expected ({})!".format(used_version_str, target_version_str))
        result_path = os.path.normpath(os.path.join(sdk_cmake_path, used_version_str, 'bin'))
  if result_path is None:
    print(">\tcmake not found under ANDROID_HOME! Searching in PATH...")
    sys_cmake_path = shutil.which('cmake')
    if sys_cmake_path is not None:
      sys_cmake_version_str = get_cmake_version(sys_cmake_path)
      sys_cmake_version = version_to_int_tuple(sys_cmake_version_str)
      if sys_cmake_version >= target_version:
        if sys_cmake_version != target_version:
          print("> WARN: Using newer version of cmake ({}), than expected ({})!".format(sys_cmake_version_str, target_version_str))
        result_path, _ = os.path.split(sys_cmake_path)
        used_version_str = sys_cmake_version_str
  if result_path is None:
    print("> ERROR: Failed to detect expected ({}) or newer cmake!".format(target_version_str))
    exit(1)
  print("\tUsing cmake {} under: {}".format(used_version_str, result_path))
  return result_path

def get_gradle_path(verbose=False, prefer_system_gradle=False):
  if prefer_system_gradle:
    result_path = shutil.which('gradle')
    if result_path:
      if verbose:
        print("\tUsing gradle at: {}".format(result_path))
      return result_path
    else:
      print("\tWARNING: gradle not found in path, using local gradle.")
  if platform.system() == "Windows":
    result_path = "gradlew.bat"
  else:
    result_path = './gradlew'
  return result_path

def get_cmake_version(cmake_path: str) -> Optional[str]:
  '''If cmake exists under given path, returns it's version.
  Otherwise returns None
  Args:
      cmake_path (str): Path to the cmake
  '''
  res = get_app_version(cmake_path)
  if res is not None:
    version = res.splitlines()[0]
    if version.startswith("cmake version"):
      res = version.strip("cmake version ")
  return res

def get_app_version(app_path: str) -> Optional[str]:
  '''If current path exists, calls it with '--version' param
  and returns result string. Otherwise returns None.
  Args:
      app_path (str): Path to the app
  '''
  res = None
  if app_path is not None:
    _, res, _ = run([ app_path, '--version' ], do_prints=False, failure_callback = lambda x: (None, None, None))
  return res

# Helper method to translate the {build, clean, and config} parameters
# used for building the app_framework and apps.
def translate_default_arguments(build_args, default_config=CONFIG_CHOICE):
  is_arg_build_none = build_args.build is None
  is_arg_clean_none = build_args.clean is None
  is_arg_build_empty = not is_arg_build_none and len(build_args.build) == 0
  is_arg_clean_empty = not is_arg_clean_none and len(build_args.clean) == 0
  if is_arg_build_empty or (is_arg_build_none and is_arg_clean_none):
    build_args.build = TARGETS_CHOICE
  elif is_arg_build_none:
    build_args.build = []
  if is_arg_clean_empty:
    build_args.clean = TARGETS_CHOICE
  elif is_arg_clean_none:
    build_args.clean = []
  if not build_args.config:
    build_args.config = default_config

def version_to_int_tuple(version: str) -> tuple:
  '''Convert a version string to a tuple of ints

  Args:
    version: version string in format xxx.xxx.xxx
  '''
  if version:
    version = version.strip()

  if not version:
    print("Invalid version string")
    return tuple()

  m = CMAKE_VERSION_PATTERN.match(version)
  if not m:
    print("Invalid version string: {}".format(version))
    return tuple()

  return tuple([int(x) for x in m.group().split(".")])


def get_ndk_path(target_version_str: str = '25.0.8775105') -> str:
  '''Get path to NDK directory
  If ANDROID_NDK_ROOT env var is set, it will be returned.
  Otherwise the ANDROID_SDK_ROOT/ndk directory will be searched for
  existing NDKs. If a version matching target_version is available,
  it will be returned. If not, a newer version will be returned or an
  error if none or only older versions are found.
  Note: ANDROID_SDK_ROOT or ANDROID_HOME need to be set.
  Args:
    target_version_str: version string in format xxx.xxx.xxx
  '''
  ndk_dir = os.environ.get("ANDROID_NDK_ROOT")
  if ndk_dir is None:
    sdk_root = get_sdk_root()
    if sdk_root is None:
      exit(1)
    target_version = version_to_int_tuple(target_version_str)
    ndk_dirs_root = os.path.join(sdk_root, "ndk")
    ndk_versions = sorted([version_to_int_tuple(f.name) for f in os.scandir(ndk_dirs_root) if f.is_dir()])
    if target_version in ndk_versions:
      ndk_dir = os.path.join(ndk_dirs_root, target_version_str)
    elif ndk_versions[-1] > target_version:
      print("> WARN: Using newer version of NDK ({}), than expected ({})!".format(ndk_versions[-1], target_version_str))
      ndk_version_str = '.'.join(map(str, ndk_versions[-1]))
      ndk_dir = os.path.join(ndk_dirs_root, ndk_version_str)
    else:
      print("> ERROR: Failed to detect expected ({}) or newer Android NDK!".format(target_version_str))
      exit(1)
  print("Using NDK at {}".format(ndk_dir))
  return ndk_dir

def get_sdk_root() -> Optional[str]:
  '''Get path to SDK root directory
  If ANDROID_HOME env var is set, it will be returned.
  Otherwise the ANDROID_SDK_ROOT evn var will be returned or None.
  '''
  sdk_root = os.environ.get('ANDROID_HOME')
  if sdk_root is None:
    sdk_root = os.environ.get('ANDROID_SDK_ROOT')
  if sdk_root is None:
    print("> ERROR: Failed to detect either ANDROID_HOME or ANDROID_SDK_ROOT variables!")
  return sdk_root
if __name__ == "__main__":
  print("Silly human.  This script does nothing on its own.  Look elsewhere.")