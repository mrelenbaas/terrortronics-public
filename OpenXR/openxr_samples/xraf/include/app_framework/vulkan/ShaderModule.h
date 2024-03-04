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
#include "../Resources.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

namespace ml {

class XrCore;

namespace Vulkan {

class ShaderModule {
 public:
  ShaderModule(XrCore *core, vk::Device device,
               const std::vector<uint8_t> &data);
  ShaderModule(XrCore *core, vk::Device device, ml::Resources::Resource shader);
  ~ShaderModule();
  vk::ShaderModule module() {
    return shader_module_;
  }

 private:
  vk::Device device_;
  vk::ShaderModule shader_module_;
};
}  // namespace Vulkan
}  // namespace ml

#endif
