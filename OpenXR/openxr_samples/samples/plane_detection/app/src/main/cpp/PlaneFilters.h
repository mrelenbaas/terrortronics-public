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

#include <app_framework/Extensions/ExtPlaneDetection.h>

#include <vector>

namespace ml {

struct PlaneFilters {
  PlaneFilters()
      : show_bounding_boxes(true),
        show_vertices(false),
        show_holes(false),
        horizontal_upward(true),
        horizontal_downward(true),
        vertical(true),
        arbitrary(true),
        floors(true),
        walls(true),
        ceilings(true),
        platforms(true) {
  }

  std::vector<XrPlaneDetectorOrientationEXT> GetOrientations() const {
    std::vector<XrPlaneDetectorOrientationEXT> orientations;

    if (vertical) {
      orientations.push_back(XR_PLANE_DETECTOR_ORIENTATION_VERTICAL_EXT);
    }
    if (horizontal_upward) {
      orientations.push_back(
          XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_UPWARD_EXT);
    }
    if (horizontal_downward) {
      orientations.push_back(
          XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_DOWNWARD_EXT);
    }
    if (arbitrary) {
      orientations.push_back(XR_PLANE_DETECTOR_ORIENTATION_ARBITRARY_EXT);
    }
    return orientations;
  }

  std::vector<XrPlaneDetectorSemanticTypeEXT> GetSemanticTypes() const {
    std::vector<XrPlaneDetectorSemanticTypeEXT> semanticTypes;
    if (ceilings) {
      semanticTypes.push_back(XR_PLANE_DETECTOR_SEMANTIC_TYPE_CEILING_EXT);
    }
    if (floors) {
      semanticTypes.push_back(XR_PLANE_DETECTOR_SEMANTIC_TYPE_FLOOR_EXT);
    }
    if (walls) {
      semanticTypes.push_back(XR_PLANE_DETECTOR_SEMANTIC_TYPE_WALL_EXT);
    }
    if (platforms) {
      semanticTypes.push_back(XR_PLANE_DETECTOR_SEMANTIC_TYPE_PLATFORM_EXT);
    }
    return semanticTypes;
  }

  bool show_bounding_boxes;
  bool show_vertices;
  bool show_holes;

  bool horizontal_upward;
  bool horizontal_downward;
  bool vertical;
  bool arbitrary;

  bool floors;
  bool walls;
  bool ceilings;
  bool platforms;
};
}  // namespace ml
