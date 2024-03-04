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

#include "../include/app_framework/vulkan/RenderTarget.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../include/app_framework/vulkan/RenderPass.h"

using namespace ml::Vulkan;

RenderTarget::RenderTarget(vk::Device device) : device_(device) {
}

RenderTarget::~RenderTarget() {
  Clear();
}

void RenderTarget::Clear() {
  if (frame_buffer_) {
    device_.destroy(frame_buffer_);
    frame_buffer_ = VK_NULL_HANDLE;
  }
  for (auto &image_view : image_views_) {
    device_.destroyImageView(image_view);
  }
  image_views_.clear();
}

void RenderTarget::Bind(vk::Image color_image, vk::Image depth_image,
                        vk::Extent2D size, RenderPass *render_pass) {
  Clear();
  // Bind color image view
  if (color_image) {
    vk::ImageViewCreateInfo imageViewCreateInfo(
        {}, color_image, vk::ImageViewType::e2D, render_pass->GetImageFormat(),
        {}, {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
    image_views_.push_back(device_.createImageView(imageViewCreateInfo));
  }

  // Bind depth image view
  if (depth_image) {
    vk::ImageViewCreateInfo imageViewCreateInfo(
        {}, depth_image, vk::ImageViewType::e2D,
        render_pass->GetDepthImageFormat(), {},
        {vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1});
    image_views_.push_back(device_.createImageView(imageViewCreateInfo));
  }

  vk::FramebufferCreateInfo framebufferCreateInfo(
      vk::FramebufferCreateFlags(), render_pass->Get(), image_views_,
      size.width, size.height, 1);

  frame_buffer_ = device_.createFramebuffer(framebufferCreateInfo);
}

void RenderTarget::Bind(ImageBufferPtr &image_buffer, RenderPass *render_pass) {
  std::vector<vk::ImageView> image_views = {image_buffer->ImageView()};

  vk::FramebufferCreateInfo framebufferCreateInfo(
      vk::FramebufferCreateFlags(), render_pass->Get(), image_views,
      image_buffer->Width(), image_buffer->Height(), 1);

  frame_buffer_ = device_.createFramebuffer(framebufferCreateInfo);
}
#endif