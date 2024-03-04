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

#ifdef XR_USE_PLATFORM_ML

#include "../include/app_framework/Extensions/MLCompat.h"

#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

std::vector<std::string> MLCompat::RequiredExtensions() {
  return std::vector<std::string>{XR_ML_COMPAT_EXTENSION_NAME};
}

MLCompat::MLCompat(ml::XrCore *core)
    : core_(core), xrCreateSpaceFromCoordinateFrameUIDML_(nullptr) {
  if (!core_->IsExtensionEnabled(XR_ML_COMPAT_EXTENSION_NAME)) {
    throw std::runtime_error(XR_ML_COMPAT_EXTENSION_NAME
                             " extension not enabled!");
  }

  bool success = true;
  success &=
      xrGetInstanceProcAddr(
          core_->Instance(), "xrCreateSpaceFromCoordinateFrameUIDML",
          (PFN_xrVoidFunction *)&xrCreateSpaceFromCoordinateFrameUIDML_) ==
      XR_SUCCESS;
  if (!success) {
    throw std::runtime_error("Missing symbols!");
  }
}

#endif
