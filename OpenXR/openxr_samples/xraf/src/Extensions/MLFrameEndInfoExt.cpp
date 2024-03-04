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

#include "../include/app_framework/Extensions/MLFrameEndInfoExt.h"

#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

std::vector<std::string> MLFrameEndInfo::RequiredExtensions() {
  return std::vector<std::string>{XR_ML_FRAME_END_INFO_EXTENSION_NAME};
}

MLFrameEndInfo::MLFrameEndInfo(ml::XrCore* core) : core_(core) {
  if (!core_->IsExtensionEnabled(XR_ML_FRAME_END_INFO_EXTENSION_NAME)) {
    throw std::runtime_error(XR_ML_FRAME_END_INFO_EXTENSION_NAME
                             " extension not enabled!");
  }
  xr_end_frame_info_ext_ = XrFrameEndInfoML{.type = XR_TYPE_FRAME_END_INFO_ML,
                                            .next = nullptr,
                                            .focusDistance = 0.0f,
                                            .flags = 0};
  core_->GetFrameEndInfoNextChain().AddStructure(
      reinterpret_cast<XrBaseInStructure*>(&xr_end_frame_info_ext_));
}

MLFrameEndInfo::~MLFrameEndInfo() {
  core_->GetFrameEndInfoNextChain().RemoveStructure(
      reinterpret_cast<XrBaseInStructure*>(&xr_end_frame_info_ext_));
}
bool MLFrameEndInfo::IsVignetteEnabled() const {
  return xr_end_frame_info_ext_.flags & XR_FRAME_END_INFO_VIGNETTE_BIT_ML;
}

void MLFrameEndInfo::SetIsVignetteEnabled(bool is_enabled) {
  if (is_enabled) {
    xr_end_frame_info_ext_.flags |= XR_FRAME_END_INFO_VIGNETTE_BIT_ML;
  } else {
    xr_end_frame_info_ext_.flags &= ~XR_FRAME_END_INFO_VIGNETTE_BIT_ML;
  }
}

bool MLFrameEndInfo::IsProtectedEnabled() const {
  return xr_end_frame_info_ext_.flags & XR_FRAME_END_INFO_PROTECTED_BIT_ML;
}

void MLFrameEndInfo::SetIsProtectedEnabled(bool is_enabled) {
  if (is_enabled) {
    xr_end_frame_info_ext_.flags |= XR_FRAME_END_INFO_PROTECTED_BIT_ML;
  } else {
    xr_end_frame_info_ext_.flags &= ~XR_FRAME_END_INFO_PROTECTED_BIT_ML;
  }
}

float MLFrameEndInfo::GetFocusDistance() const {
  return xr_end_frame_info_ext_.focusDistance;
}

void MLFrameEndInfo::SetFocusDistance(float focus_distance) {
  xr_end_frame_info_ext_.focusDistance =
      std::clamp(focus_distance, 0.f, 1000.f);
}
