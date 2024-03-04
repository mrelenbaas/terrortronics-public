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

#include "../include/app_framework/Extensions/MLMarkerTracking.h"

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

MLMarkerTracking::MLMarkerTracking(XrCore *core) : core_(core) {
  if (!core_->IsExtensionEnabled(XR_ML_MARKER_UNDERSTANDING_EXTENSION_NAME)) {
    throw std::runtime_error(XR_ML_MARKER_UNDERSTANDING_EXTENSION_NAME
                             " extension not enabled!");
  }
  marker_detector_ = XR_NULL_HANDLE;

  struct FunctionEntry {
    const char *name;
    PFN_xrVoidFunction *function;
  };

  std::vector<FunctionEntry> function_list = {
      {"xrCreateMarkerDetectorML",
       (PFN_xrVoidFunction *)&xrCreateMarkerDetectorML_},
      {"xrDestroyMarkerDetectorML",
       (PFN_xrVoidFunction *)&xrDestroyMarkerDetectorML_},
      {"xrSnapshotMarkerDetectorML",
       (PFN_xrVoidFunction *)&xrSnapshotMarkerDetectorML_},
      {"xrGetMarkerDetectorStateML",
       (PFN_xrVoidFunction *)&xrGetMarkerDetectorStateML_},
      {"xrGetMarkersML", (PFN_xrVoidFunction *)&xrGetMarkersML_},
      {"xrGetMarkerReprojectionErrorML",
       (PFN_xrVoidFunction *)&xrGetMarkerReprojectionErrorML_},
      {"xrGetMarkerLengthML", (PFN_xrVoidFunction *)&xrGetMarkerLengthML_},
      {"xrGetMarkerNumberML", (PFN_xrVoidFunction *)&xrGetMarkerNumberML_},
      {"xrGetMarkerStringML", (PFN_xrVoidFunction *)&xrGetMarkerStringML_},
      {"xrCreateMarkerSpaceML", (PFN_xrVoidFunction *)&xrCreateMarkerSpaceML_}};

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

void MLMarkerTracking::CreateTracker(XrMarkerDetectorCreateInfoML createInfo) {
  auto result = xrCreateMarkerDetectorML_(core_->Session(), &createInfo,
                                          &marker_detector_);

  if (result != XR_SUCCESS) {
    throw std::runtime_error("Unable to create Marker Tracking object.");
  }
}

void MLMarkerTracking::CreateMarkerSpace(XrMarkerSpaceCreateInfoML *createInfo,
                                         XrSpace *space) {
  createInfo->markerDetector = marker_detector_;

  auto result = xrCreateMarkerSpaceML_(core_->Session(), createInfo, space);
  if (result != XR_SUCCESS) {
    throw std::runtime_error("Unable to create space.");
  }
}

void MLMarkerTracking::DestroyTracker() {
  if (marker_detector_ != XR_NULL_HANDLE) {
    xrDestroyMarkerDetectorML_(marker_detector_);
    marker_detector_ = XR_NULL_HANDLE;
  }
}

MLMarkerTracking::~MLMarkerTracking() {
  DestroyTracker();
}

std::vector<std::string> MLMarkerTracking::RequiredExtensions() {
  return {XR_ML_MARKER_UNDERSTANDING_EXTENSION_NAME};
}
