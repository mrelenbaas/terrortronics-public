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

#pragma once

#include "../Linear.h"

namespace ml {
namespace Vulkan {

struct PushConstants {
  enum Flags {
    USE_TEXTURE = 1 << 0,
    USE_MATERIAL = 1 << 1,
    USE_NORMAL_MAP = 1 << 2,
    USE_AO_MAP = 1 << 3,
    USE_EMISSIVE_MAP = 1 << 4,
  };
  PushConstants() : material{1.0f, 1.0f, 0.0f, 0.0f}, view_flags(0){};

  XrMatrix4x4f model_matrix;
  // material
  XrColor4f base_color;
  XrVector4f material;  // x = roughness, y = metallic
  XrColor4f emissive_factor;
  float ambient_occlusion_strength;
  uint32_t view_flags;
  uint32_t view_index;

  void AddFlag(Flags flag) {
    view_flags |= (uint32_t)flag;
  }
  void SetView(uint32_t view) {
    view_index = view;
  }
  void SetRoughness(float value) {
    material.x = value;
  }
  void SetMetallic(float value) {
    material.y = value;
  }
};
}  // namespace Vulkan
}  // namespace ml