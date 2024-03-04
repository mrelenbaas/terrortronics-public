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

#pragma once

#include <openxr/openxr.h>

#include <algorithm>
#include <string>
#include <vector>

#include "../../addon_headers/XR_ML_marker_understanding.h"

namespace ml {

class XrCore;

namespace Extensions {

/*! \brief Plane Detection
 *
 * This class implements support XR_ML_user_calibration extension.
 *
 * ToDo: Add public url once extension is published.
 *
 */
class MLMarkerTracking {
 public:
  MLMarkerTracking(XrCore* core);
  ~MLMarkerTracking();

  void CreateTracker(XrMarkerDetectorCreateInfoML createInfo);
  void DestroyTracker();

  void CreateMarkerSpace(XrMarkerSpaceCreateInfoML* createInfo, XrSpace* space);

  static std::vector<std::string> RequiredExtensions();

  XrResult xrSnapshotMarkerDetectorML(
      XrMarkerDetectorSnapshotInfoML* snapshotInfo) {
    return xrSnapshotMarkerDetectorML_(marker_detector_, snapshotInfo);
  }

  XrResult xrGetMarkerDetectorStateML(XrMarkerDetectorStateML* stateInfo) {
    return xrGetMarkerDetectorStateML_(marker_detector_, stateInfo);
  }

  XrResult xrGetMarkersML(uint32_t markerAtomCapacityInput,
                          uint32_t* markerAtomCountOutput,
                          XrMarkerML* markerAtoms) {
    return xrGetMarkersML_(marker_detector_, markerAtomCapacityInput,
                           markerAtomCountOutput, markerAtoms);
  }

  XrResult xrGetMarkerReprojectionErrorML(XrMarkerML markerAtom,
                                          float* reprojectionErrorMeters) {
    return xrGetMarkerReprojectionErrorML_(marker_detector_, markerAtom,
                                           reprojectionErrorMeters);
  }

  XrResult xrGetMarkerLengthML(XrMarkerML markerAtom, float* meters) {
    return xrGetMarkerLengthML_(marker_detector_, markerAtom, meters);
  }

  XrResult xrGetMarkerNumberML(XrMarkerML markerAtom, uint64_t* number) {
    return xrGetMarkerNumberML_(marker_detector_, markerAtom, number);
  }

  XrResult xrGetMarkerStringML(XrMarkerML markerAtom,
                               uint32_t bufferCapacityInput,
                               uint32_t* bufferCountOutput, char* buffer) {
    return xrGetMarkerStringML_(marker_detector_, markerAtom,
                                bufferCapacityInput, bufferCountOutput, buffer);
  }

 private:
  XrCore* core_;
  XrMarkerDetectorML marker_detector_;

  PFN_xrCreateMarkerDetectorML xrCreateMarkerDetectorML_;
  PFN_xrDestroyMarkerDetectorML xrDestroyMarkerDetectorML_;
  PFN_xrSnapshotMarkerDetectorML xrSnapshotMarkerDetectorML_;
  PFN_xrGetMarkerDetectorStateML xrGetMarkerDetectorStateML_;
  PFN_xrGetMarkersML xrGetMarkersML_;
  PFN_xrGetMarkerReprojectionErrorML xrGetMarkerReprojectionErrorML_;
  PFN_xrGetMarkerLengthML xrGetMarkerLengthML_;
  PFN_xrGetMarkerNumberML xrGetMarkerNumberML_;
  PFN_xrGetMarkerStringML xrGetMarkerStringML_;
  PFN_xrCreateMarkerSpaceML xrCreateMarkerSpaceML_;
};

}  // namespace Extensions

}  // namespace ml
