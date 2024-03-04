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

#include "../include/app_framework/Extensions/MLSystemNotifications.h"

#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

std::vector<std::string> MLSystemNotifications::RequiredExtensions() {
  return std::vector<std::string>{XR_ML_SYSTEM_NOTIFICATIONS_EXTENSION_NAME};
}

MLSystemNotifications::MLSystemNotifications(ml::XrCore* core) : core_(core) {
  if (!core_->IsExtensionEnabled(XR_ML_SYSTEM_NOTIFICATIONS_EXTENSION_NAME)) {
    throw std::runtime_error(XR_ML_SYSTEM_NOTIFICATIONS_EXTENSION_NAME
                             " extension not enabled!");
  }
  const bool success =
      xrGetInstanceProcAddr(
          core_->Instance(), "xrSetSystemNotificationsML",
          (PFN_xrVoidFunction*)&xrSetSystemNotificationsML_) == XR_SUCCESS;

  if (!success) {
    throw std::runtime_error("Missing symbols!");
  }

  XrSystemNotificationsPropertiesML system_notifications_system_properties{
      .type = XR_TYPE_SYSTEM_NOTIFICATIONS_PROPERTIES_ML,
      .next = nullptr,
      .supportedFeatures = 0};
  XrSystemProperties properties{
      .type = XR_TYPE_SYSTEM_PROPERTIES,
      .next = &system_notifications_system_properties};

  if (xrGetSystemProperties(core->Instance(), core->SystemId(), &properties) !=
      XR_SUCCESS) {
    throw std::runtime_error("Unable to to query system properties.");
  }
  supported_features_ =
      system_notifications_system_properties.supportedFeatures;
}

MLSystemNotifications::~MLSystemNotifications() {
}

XrResult MLSystemNotifications::SetIsSuppressed(bool is_suppressed) {
  XrSystemNotificationsSetInfoML set_info{
      .type = XR_TYPE_SYSTEM_NOTIFICATIONS_SET_INFO_ML,
      .next = nullptr,
      .suppressNotifications = is_suppressed};
  return xrSetSystemNotificationsML_(core_->Instance(), &set_info);
}

bool MLSystemNotifications::IsSupported(uint64_t flag) const {
  return supported_features_ & flag;
}
