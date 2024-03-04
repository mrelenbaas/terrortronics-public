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

#include "../GuiBackend.h"
#include "../OpenXRCommon.h"
#include "CommandBuffers.h"
#include "ImageBuffer.h"
#include "RenderPass.h"
#include "RenderTarget.h"

namespace ml {

class XrCore;

namespace Vulkan {

class VulkanImGui : public GuiBackend {
 public:
  struct GuiCreateInfo {
    XrCore *core;
    vk::Instance instance;
    vk::PhysicalDevice physical_device;
    vk::Device device;
    ml::Vulkan::CommandBuffer command_buffer;
    vk::Queue queue;
    uint32_t width;
    uint32_t height;
    VmaAllocator allocator;
    vk::DescriptorSetLayout descriptor_set_layout;
  };

  VulkanImGui(const GuiCreateInfo &create_info);
  ~VulkanImGui();

  void Render(vk::CommandBuffer command_buffer, vk::Queue queue);

  ImageBufferPtr ImageBuffer() const {
    return image_buffer_;
  }
  Vulkan::RenderPass *RenderPass() const {
    return render_pass_.get();
  }
  Vulkan::RenderTarget *RenderTarget() const {
    return render_target_.get();
  }
  void FrameBufferSize(uint32_t &width, uint32_t &height) const override {
    width = create_info_.width;
    height = create_info_.height;
  }

 private:
  GuiCreateInfo create_info_;
  VkDescriptorPool pool_;

  ImageBufferPtr image_buffer_;
  std::unique_ptr<Vulkan::RenderPass> render_pass_;
  std::unique_ptr<Vulkan::RenderTarget> render_target_;

  void PrepareRenderPass();
  vk::DescriptorSetLayout CreateLayout();
};
}  // namespace Vulkan
}  // namespace ml