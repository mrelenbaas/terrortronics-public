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

namespace ml {
namespace Vulkan {
class RenderPass {
 public:
  // depth buffer
  RenderPass(vk::Device device, vk::Format image_format,
             vk::Format depth_image_format);

  RenderPass(vk::Device device, vk::Format image_format,
             vk::Format depth_image_format,
             std::vector<vk::AttachmentDescription> attachments,
             std::vector<vk::SubpassDependency> dependencies);

  ~RenderPass();

  // no copy or assigning please.
  RenderPass(const RenderPass &) = delete;
  RenderPass &operator=(RenderPass const &) = delete;

  inline vk::RenderPass &Get() {
    return render_pass_;
  }
  inline vk::Format &GetDepthImageFormat() {
    return depth_image_format_;
  }
  inline vk::Format &GetImageFormat() {
    return image_format_;
  }

 private:
  vk::Device device_;
  vk::Format image_format_;
  vk::Format depth_image_format_;
  vk::RenderPass render_pass_;
};
}  // namespace Vulkan
}  // namespace ml

#endif