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

namespace ml {

class XrCore;

namespace Extensions {

/*! \brief Plane Detection
 *
 *
 * https://www.khronos.org/registry/OpenXR/specs/1.0/html/xrspec.html#XR_EXT_plane_detection
 *
 */
class ExtPlaneDetection {
 public:
  ExtPlaneDetection(XrCore* core, bool enable_hull);
  ~ExtPlaneDetection();
  static std::vector<std::string> RequiredExtensions();

  /*! \brief Returns true if plane detection is supported, false otherwise. */
  bool IsSupported(uint64_t flag) const;

  XrResult xrBeginPlaneDetectionEXT(
      const XrPlaneDetectorBeginInfoEXT* beginInfo) {
    return xrBeginPlaneDetectionEXT_(plane_detector_, beginInfo);
  }

  XrResult xrGetPlaneDetectionStateEXT(XrPlaneDetectionStateEXT* state) {
    return xrGetPlaneDetectionStateEXT_(plane_detector_, state);
  }

  XrResult xrGetPlaneDetectionsEXT(const XrPlaneDetectorGetInfoEXT* info,
                                   XrPlaneDetectorLocationsEXT* locations) {
    return xrGetPlaneDetectionsEXT_(plane_detector_, info, locations);
  }

  XrResult xrGetPlanePolygonBufferEXT(
      uint32_t planeId, uint32_t polygonBufferIndex,
      XrPlaneDetectorPolygonBufferEXT* polygonBuffer) {
    return xrGetPlanePolygonBufferEXT_(plane_detector_, planeId,
                                       polygonBufferIndex, polygonBuffer);
  }

 private:
  XrCore* core_;
  PFN_xrCreatePlaneDetectorEXT xrCreatePlaneDetectorEXT_;
  PFN_xrDestroyPlaneDetectorEXT xrDestroyPlaneDetectorEXT_;
  PFN_xrBeginPlaneDetectionEXT xrBeginPlaneDetectionEXT_;
  PFN_xrGetPlaneDetectionStateEXT xrGetPlaneDetectionStateEXT_;
  PFN_xrGetPlaneDetectionsEXT xrGetPlaneDetectionsEXT_;
  PFN_xrGetPlanePolygonBufferEXT xrGetPlanePolygonBufferEXT_;

  XrPlaneDetectorEXT plane_detector_;
  XrFlags64 supported_features_;
};

}  // namespace Extensions

}  // namespace ml
