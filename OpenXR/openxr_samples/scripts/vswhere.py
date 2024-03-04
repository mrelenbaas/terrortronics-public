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

import json
import locale

from mlsdk_helpers import *


def get_vswhere_results():
    jsonret = _run_and_decode_vswhere(True, True)
    if not jsonret:
        jsonret = _run_and_decode_vswhere(False)
    return [VsWhereResult(json_obj) for json_obj in jsonret]


def _get_vswhere_path():
    vswhere_file_path = os.path.join(
        os.environ.get("ProgramFiles(x86)", '.'),
        "Microsoft Visual Studio",
        "Installer",
        "vswhere.exe"
    )
    return vswhere_file_path


def _run_and_decode_vswhere(try_utf8, suppress_errors=False):
    """
    vswhere emitted JSON content in a non-JSON and non-UTF8 format until Jun 2018.
    On non-English locales, the content may have non-ASCII text in the "Description"
    field of a tool entry.  Either subprocess.run() would explode here (using
    universal_newlines=True only allows running with the default locale in Python 3.5)
    or the JSON decoder would explode, not getting proper text (i.e. some Japanese
    locales could emit what looks like '\' in the text).

    So this is called twice, once hoping that the UTF-8 option is available, and decoding that
    way, or, if that fails, running without that parameters and trying to decode
    in different ways.

    :param try_utf8: decode as UTF8
    :param suppress_errors: if True, don't report if the command failed (e.g. trying to
    use the UTF-8 option)
    :return: JSON document
    """
    cmd = [
        _get_vswhere_path(),
        "-requires", "Microsoft.VisualStudio.Component.VC.Tools.x86.x64",
        "-format", "json",
    ]

    if try_utf8:
        cmd += ['-utf8']

    # Python 3.5 can't ask for an encoding here, so decode later
    out = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if out.returncode != 0 and suppress_errors:
        # likely this is because "-utf8" doesn't exist in this version.
        return None

    if try_utf8:
        encodings = ['utf-8']
    else:
        encodings = [locale.getpreferredencoding(False), "cp1252", "utf-8", "ascii"]

    for encoding in encodings:
        try:
            # The last (or only) encoding is the fallback where we throw caution to the wind
            # and hope the filesystem paths are MS defaults which are always ASCII
            handling = encoding == encodings[-1] and 'replace' or 'strict'
            stdout_text = out.stdout.decode(encoding, handling)
            stderr_text = out.stderr.decode(encoding, handling)
        except UnicodeDecodeError as ue:
            print("Failed to decode content as {} in {}:\n{}".format(encoding, ' '.join(cmd), str(ue)), file=sys.stderr)
            continue

        if out.returncode != 0:
            # suppress_errors must be False; delay reporting til here so we can show the text
            # (no need to keep looping)
            return None

        try:
            return json.loads(stdout_text)
        except json.JSONDecodeError as je:
            # likely we decoded the text but it was mangled (e.g. EUC-JP text has misleading '\' chars)
            print("Failed to decode content as {} in {} ({}):\n{}".format(encoding, ' '.join(cmd), str(je), stdout_text + stderr_text), file=sys.stderr)
            continue

    # nothing worked
    return None


class VsWhereResult(object):
    def __init__(self, json_vs_entry):
        if "installationPath" not in json_vs_entry:
            print("Wrong json entry given to VsWhereResult constructor!")
            exit(1)

        self.display_name = json_vs_entry["displayName"]
        self.install_path = json_vs_entry["installationPath"]
        self.common_tools_path = os.path.join(self.install_path, "Common7", "Tools")
        self.version_full = json_vs_entry["installationVersion"]
        self.version_major = int(json_vs_entry["installationVersion"].split('.')[0])
        self.product_line_version = json_vs_entry["catalog"]["productLineVersion"]
        self.product_name = json_vs_entry["catalog"]["productName"]
        self.generator_name = "{} {} {}".format(self.product_name, self.version_major, self.product_line_version)

        # Verify the install path exists.
        if not os.access(self.install_path, os.X_OK):
            print("Found {} with invalid installation path: \"{}\"".format(self.display_name, self.install_path), file=sys.stderr)
            exit(1)

        # Verify the common tools directory exists within the install path.
        if not os.access(self.common_tools_path, os.X_OK):
            print("{} does not have the required common tools path: \"{}\"".format(self.display_name, self.common_tools_path), file=sys.stderr)
            exit(1)


    def __str__(self):
        return "Generator: {}, Install path: {}".format(self.generator_name, self.install_path)