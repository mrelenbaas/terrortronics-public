#!/usr/bin/env python3
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
import sys

vi = sys.version_info
if vi.major < 3 or (vi.major == 3 and vi.minor < 5):
  print("Please run this script with Python 3.5 or newer")
  exit(1)

sys.path.insert(0, '../scripts')

from build_project import build

if __name__ == "__main__":
  root_path        = os.path.dirname(os.path.realpath( __file__))
  projects         = []
  out_path_device  = os.path.join(root_path, 'out', 'openxr_device_samples')
  out_path_host    = os.path.join(root_path, 'out', 'openxr_host_samples')
  return_code = build(root_path, out_path_device, out_path_host, projects)
  exit(return_code)




