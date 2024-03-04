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

#include "ImageBuffer.h"

namespace ml {
namespace Vulkan {
class RenderPass;
class RenderTarget {
 public:
  RenderTarget(vk::Device device);
  ~RenderTarget();

  // no copy or assigning please.
  RenderTarget(const RenderTarget &) = delete;
  RenderTarget &operator=(RenderTarget const &) = delete;

  inline vk::Framebuffer &GetFrameBuffer() {
    return frame_buffer_;
  }

  void Bind(vk::Image color_image, vk::Image depth_image, vk::Extent2D size,
            RenderPass *render_pass);

  void Bind(ImageBufferPtr &image_buffer, RenderPass *render_pass);

 private:
  vk::Device device_;
  std::vector<vk::ImageView> image_views_;
  vk::Framebuffer frame_buffer_;
  void Clear();
};

}  // namespace Vulkan

}  // namespace ml

#endif
