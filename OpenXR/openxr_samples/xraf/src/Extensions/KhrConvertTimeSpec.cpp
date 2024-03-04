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

#ifdef XR_USE_TIMESPEC

#include "../../include/app_framework/Extensions/KhrConvertTimeSpec.h"

#include "../../include/app_framework/XrCore.h"

using namespace ml::Extensions;

std::vector<std::string> KhrConvertTimeSpec::RequiredExtensions() {
  return std::vector<std::string>{XR_KHR_CONVERT_TIMESPEC_TIME_EXTENSION_NAME};
}

KhrConvertTimeSpec::KhrConvertTimeSpec(XrCore *core) : core_(core) {
  if (!core_->IsExtensionEnabled(XR_KHR_CONVERT_TIMESPEC_TIME_EXTENSION_NAME)) {
    throw std::runtime_error(XR_KHR_CONVERT_TIMESPEC_TIME_EXTENSION_NAME
                             " extension not enabled!");
  }

  bool success = true;
  success &=
      xrGetInstanceProcAddr(
          core_->Instance(), "xrConvertTimespecTimeToTimeKHR",
          (PFN_xrVoidFunction *)&xrConvertTimespecTimeToTimeKHR_) == XR_SUCCESS;
  success &=
      xrGetInstanceProcAddr(
          core_->Instance(), "xrConvertTimeToTimespecTimeKHR",
          (PFN_xrVoidFunction *)&xrConvertTimeToTimespecTimeKHR_) == XR_SUCCESS;
  if (!success) {
    throw std::runtime_error("Missing symbols!");
  }
}

XrResult KhrConvertTimeSpec::xrConvertTimespecTimeToTimeKHR(
    const struct timespec *timespecTime, XrTime *time) {
  return xrConvertTimespecTimeToTimeKHR_(core_->Instance(), timespecTime, time);
}
XrResult KhrConvertTimeSpec::xrConvertTimeToTimespecTimeKHR(
    XrTime time, struct timespec *timespecTime) {
  return xrConvertTimeToTimespecTimeKHR_(core_->Instance(), time, timespecTime);
}

#endif