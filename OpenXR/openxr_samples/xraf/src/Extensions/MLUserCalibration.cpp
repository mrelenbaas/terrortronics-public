// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2023 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#include "../include/app_framework/Extensions/MLUserCalibration.h"

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

MLUserCalibration::MLUserCalibration(XrCore *core) : core_(core) {
  if (!core_->IsExtensionEnabled(XR_ML_USER_CALIBRATION_EXTENSION_NAME)) {
    throw std::runtime_error(XR_ML_USER_CALIBRATION_EXTENSION_NAME
                             " extension not enabled!");
  }

  struct FunctionEntry {
    const char *name;
    PFN_xrVoidFunction *function;
  };

  std::vector<FunctionEntry> function_list = {
      {"xrEnableUserCalibrationEventsML",
       (PFN_xrVoidFunction *)&xrEnableUserCalibrationEventsML_}};
  for (auto &entry : function_list) {
    bool success = xrGetInstanceProcAddr(core_->Instance(), entry.name,
                                         entry.function) == XR_SUCCESS;
    if (!success) {
      std::string error = "Missing Symbol: ";
      error += entry.name;
      throw std::runtime_error(error);
    }
  }
}

MLUserCalibration::~MLUserCalibration() {
}

std::vector<std::string> MLUserCalibration::RequiredExtensions() {
  return {XR_ML_USER_CALIBRATION_EXTENSION_NAME};
}
