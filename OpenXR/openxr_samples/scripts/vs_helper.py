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

import os
import platform

from vswhere import *
from vsenvcache import *

def get_ninja_env(rescan_on_win=False, msvc=None):
    env = dict(os.environ)
    if platform.system() == "Windows":
        vs_toolinfos = get_vswhere_results()
        if vs_toolinfos:
            chosen_vs_toolinfo = None
            if msvc:
                for v in vs_toolinfos:
                    if v.generator_name == msvc:
                        chosen_vs_toolinfo = v
                        break

            if not chosen_vs_toolinfo:
                chosen_vs_toolinfo = sorted(vs_toolinfos, key=lambda x: x.version_major, reverse=True)[0]
                if msvc is not None:
                    print("\tCouldn't find chosen Visual Studio version ({}), using the newest available!".format(msvc))
            print("\tUsing {}".format(chosen_vs_toolinfo))
            env_cache = VsEnvCache(chosen_vs_toolinfo)
            env_cache.detect(rescan_on_win)
            env_cache.update_env(env)

    return os.environ
