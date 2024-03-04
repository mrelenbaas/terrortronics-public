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

#include "../OpenXRCommon.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../Linear.h"
#include "Buffer.h"

namespace ml {
namespace Vulkan {

#define MAX_LIGHTS 4

struct LightSource {
  XrVector4f pos;
  XrColor4f color;
  enum Flags {
    ENABLED = 1 << 0,
  };
  uint32_t flags;
  uint32_t pad1;
  uint32_t pad2;
  uint32_t pad3;
};

struct View {
  XrMatrix4x4f projection_matrix;
  XrMatrix4x4f view_matrix;
  XrVector4f camera_pos;
};

struct UBODataModel {
  View view[2];
  LightSource light_sources[MAX_LIGHTS];
};

class UBO : public Buffer {
 public:
  UBO(vk::Device device, VmaAllocator allocator);
  ~UBO();
  inline UBODataModel &Get() {
    return ubo_;
  }
  void Sync();

  vk::DescriptorSetLayout &Layout() {
    return layout_;
  }

  vk::DescriptorSet &DescriptorSet() {
    return descriptor_set_;
  }

 protected:
  void CreateLayout();
  void AllocateDescriptorSet();
  vk::DescriptorSetLayout layout_;
  vk::DescriptorPool descriptor_pool_;
  vk::DescriptorSet descriptor_set_;
  vk::Device device_;
  UBODataModel ubo_;
};
}  // namespace Vulkan

}  // namespace ml

#endif
