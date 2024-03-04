// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include "../OpenXRCommon.h"

#ifdef XR_USE_TIMESPEC
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

#include <string>
#include <vector>

namespace ml {

class XrCore;

namespace Extensions {

class KhrConvertTimeSpec {
 public:
  KhrConvertTimeSpec(XrCore* core);

  static std::vector<std::string> RequiredExtensions();

  XrResult xrConvertTimespecTimeToTimeKHR(const struct timespec* timespecTime,
                                          XrTime* time);

  XrResult xrConvertTimeToTimespecTimeKHR(XrTime time,
                                          struct timespec* timespecTime);

 private:
  XrCore* core_;
  PFN_xrConvertTimeToTimespecTimeKHR xrConvertTimeToTimespecTimeKHR_;
  PFN_xrConvertTimespecTimeToTimeKHR xrConvertTimespecTimeToTimeKHR_;
};

}  // namespace Extensions

}  // namespace ml

#endif