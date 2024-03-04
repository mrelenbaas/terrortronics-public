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

#include "../include/app_framework/Extensions/MLGlobalDimmer.h"

#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

std::vector<std::string> MLGlobalDimmer::RequiredExtensions() {
  return std::vector<std::string>{XR_ML_GLOBAL_DIMMER_EXTENSION_NAME};
}

MLGlobalDimmer::MLGlobalDimmer(ml::XrCore* core) : core_(core) {
  if (!core_->IsExtensionEnabled(XR_ML_GLOBAL_DIMMER_EXTENSION_NAME)) {
    throw std::runtime_error(XR_ML_GLOBAL_DIMMER_EXTENSION_NAME
                             " extension not enabled!");
  }
  xr_global_dimmer_frame_end_info_ = XrGlobalDimmerFrameEndInfoML{
      .type = XR_TYPE_GLOBAL_DIMMER_FRAME_END_INFO_ML,
      .next = nullptr,
      .dimmerValue = 0.f,
      .flags = 0};
  core_->GetFrameEndInfoNextChain().AddStructure(
      reinterpret_cast<XrBaseInStructure*>(&xr_global_dimmer_frame_end_info_));
}

MLGlobalDimmer::~MLGlobalDimmer() {
  core_->GetFrameEndInfoNextChain().RemoveStructure(
      reinterpret_cast<XrBaseInStructure*>(&xr_global_dimmer_frame_end_info_));
}

void MLGlobalDimmer::SetValue(float dimmer_value) {
  xr_global_dimmer_frame_end_info_.dimmerValue =
      std::clamp(dimmer_value, 0.f, 1.f);
}

void MLGlobalDimmer::SetIsEnabled(bool is_enabled) {
  xr_global_dimmer_frame_end_info_.flags =
      is_enabled ? XR_GLOBAL_DIMMER_FRAME_END_INFO_ENABLED_BIT_ML : 0;
}

float MLGlobalDimmer::Value() const {
  return xr_global_dimmer_frame_end_info_.dimmerValue;
}

bool MLGlobalDimmer::IsEnabled() const {
  return xr_global_dimmer_frame_end_info_.flags &
         XR_GLOBAL_DIMMER_FRAME_END_INFO_ENABLED_BIT_ML;
}
