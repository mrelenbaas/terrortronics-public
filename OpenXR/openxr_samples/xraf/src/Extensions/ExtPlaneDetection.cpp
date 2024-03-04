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

#include "../include/app_framework/Extensions/ExtPlaneDetection.h"

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

ExtPlaneDetection::ExtPlaneDetection(XrCore *core, bool enable_hull)
    : core_(core), plane_detector_(XR_NULL_HANDLE) {
  if (!core_->IsExtensionEnabled(XR_EXT_PLANE_DETECTION_EXTENSION_NAME)) {
    throw std::runtime_error(XR_EXT_PLANE_DETECTION_EXTENSION_NAME
                             " extension not enabled!");
  }

  XrSystemPlaneDetectionPropertiesEXT plane_detection_system_properties{
      .type = XR_TYPE_SYSTEM_PLANE_DETECTION_PROPERTIES_EXT, .next = nullptr};

  XrSystemProperties properties{.type = XR_TYPE_SYSTEM_PROPERTIES,
                                .next = &plane_detection_system_properties};

  if (xrGetSystemProperties(core->Instance(), core->SystemId(), &properties) !=
      XR_SUCCESS) {
    throw std::runtime_error("Unable to to query system properties.");
  }

  supported_features_ = plane_detection_system_properties.supportedFeatures;

  XrPlaneDetectorCreateInfoEXT create_info{
      .type = XR_TYPE_PLANE_DETECTOR_CREATE_INFO_EXT,
      .next = nullptr,
      .flags = enable_hull ? XR_PLANE_DETECTOR_ENABLE_CONTOUR_BIT_EXT : 0};

  struct FunctionEntry {
    const char *name;
    PFN_xrVoidFunction *function;
  };

  std::vector<FunctionEntry> function_list = {
      {"xrCreatePlaneDetectorEXT",
       (PFN_xrVoidFunction *)&xrCreatePlaneDetectorEXT_},
      {"xrDestroyPlaneDetectorEXT",
       (PFN_xrVoidFunction *)&xrDestroyPlaneDetectorEXT_},
      {"xrBeginPlaneDetectionEXT",
       (PFN_xrVoidFunction *)&xrBeginPlaneDetectionEXT_},
      {"xrGetPlaneDetectionStateEXT",
       (PFN_xrVoidFunction *)&xrGetPlaneDetectionStateEXT_},
      {"xrGetPlaneDetectionsEXT",
       (PFN_xrVoidFunction *)&xrGetPlaneDetectionsEXT_},
      {"xrGetPlanePolygonBufferEXT",
       (PFN_xrVoidFunction *)&xrGetPlanePolygonBufferEXT_}};
  for (auto &entry : function_list) {
    bool success = xrGetInstanceProcAddr(core_->Instance(), entry.name,
                                         entry.function) == XR_SUCCESS;
    if (!success) {
      std::string error = "Missing Symbol: ";
      error += entry.name;
      throw std::runtime_error(error);
    }
  }

  auto result = xrCreatePlaneDetectorEXT_(core_->Session(), &create_info,
                                          &plane_detector_);
  if (result != XR_SUCCESS) {
    throw std::runtime_error("Unable to create Plane Detection object.");
  }
}

ExtPlaneDetection::~ExtPlaneDetection() {
  if (plane_detector_ != XR_NULL_HANDLE) {
    xrDestroyPlaneDetectorEXT_(plane_detector_);
    plane_detector_ = XR_NULL_HANDLE;
  }
}

std::vector<std::string> ExtPlaneDetection::RequiredExtensions() {
  return {XR_EXT_PLANE_DETECTION_EXTENSION_NAME};
}

bool ExtPlaneDetection::IsSupported(uint64_t flag) const {
  return supported_features_ & flag;
}