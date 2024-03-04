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

#include "../include/app_framework/Extensions/ExtHandTracking.h"

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

std::vector<std::string> ExtHandTracking::RequiredExtensions() {
  return std::vector<std::string>{XR_EXT_HAND_TRACKING_EXTENSION_NAME};
}

ExtHandTracking::ExtHandTracking(ml::XrCore *core, XrHandEXT hand)
    : core_(core),
      tracker_(XR_NULL_HANDLE),
      xrCreateHandTrackerEXT(nullptr),
      xrDestroyHandTrackerEXT(nullptr),
      xrLocateHandJointsEXT(nullptr),
      location_info_{XR_TYPE_HAND_JOINT_LOCATIONS_EXT},
      velocity_info_{XR_TYPE_HAND_JOINT_VELOCITIES_EXT},
      locate_info_{XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT} {
  if (!core_->IsExtensionEnabled(XR_EXT_HAND_TRACKING_EXTENSION_NAME)) {
    throw std::runtime_error(XR_EXT_HAND_TRACKING_EXTENSION_NAME
                             " extension not enabled!");
  }
  if (!core_->SupportsHandTracking()) {
    throw std::runtime_error("Hand tracking not supported!");
  }

  bool success = true;
  success &= xrGetInstanceProcAddr(
                 core_->Instance(), "xrCreateHandTrackerEXT",
                 (PFN_xrVoidFunction *)&xrCreateHandTrackerEXT) == XR_SUCCESS;
  success &= xrGetInstanceProcAddr(
                 core_->Instance(), "xrDestroyHandTrackerEXT",
                 (PFN_xrVoidFunction *)&xrDestroyHandTrackerEXT) == XR_SUCCESS;
  success &= xrGetInstanceProcAddr(
                 core_->Instance(), "xrLocateHandJointsEXT",
                 (PFN_xrVoidFunction *)&xrLocateHandJointsEXT) == XR_SUCCESS;
  if (!success) {
    throw std::runtime_error("Missing symbols!");
  }

  XrHandTrackerCreateInfoEXT create_info{
      .type = XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT,
      .next = nullptr,
      .hand = hand,
      .handJointSet = XR_HAND_JOINT_SET_DEFAULT_EXT};
  if (xrCreateHandTrackerEXT(core_->Session(), &create_info, &tracker_) !=
      XR_SUCCESS) {
    throw std::runtime_error("xrCreateHandTrackerEXT failed!");
  }

  locations_.resize(XR_HAND_JOINT_COUNT_EXT);
  velocities_.resize(XR_HAND_JOINT_COUNT_EXT);

  velocity_info_.jointCount = XR_HAND_JOINT_COUNT_EXT;
  velocity_info_.jointVelocities = velocities_.data();

  location_info_.next = &velocity_info_;
  location_info_.jointCount = XR_HAND_JOINT_COUNT_EXT;
  location_info_.jointLocations = locations_.data();

  locate_info_.baseSpace = core_->WorldSpace();
}

ExtHandTracking::~ExtHandTracking() {
  if (tracker_ != XR_NULL_HANDLE) {
    xrDestroyHandTrackerEXT(tracker_);
    tracker_ = XR_NULL_HANDLE;
  }
}

bool ExtHandTracking::Locate(XrTime time, bool &is_active) {
  locate_info_.time = time;
  const auto result =
      xrLocateHandJointsEXT(tracker_, &locate_info_, &location_info_);
  if (result != XR_SUCCESS) {
    ALOGE("xrLocateHandJointsEXT failed: %d", result);
  }
  is_active = location_info_.isActive == XR_TRUE;
  return result == XR_SUCCESS;
}
