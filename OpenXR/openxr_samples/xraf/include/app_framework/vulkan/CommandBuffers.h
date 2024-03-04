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

#include "../OpenXRCommon.h"

namespace ml {
namespace Vulkan {

class CommandBuffer {
 public:
  CommandBuffer() = default;

  operator vk::CommandBuffer &() {
    return buffer_;
  }
  operator VkCommandBuffer() {
    return buffer_;
  }
  operator vk::Fence &() {
    return fence_;
  }

  // begin name convention matching vk::CommandBuffer
  void wait(bool reset = true);
  void reset();
  void begin(const vk::CommandBufferBeginInfo& beginInfo =
                 vk::CommandBufferBeginInfo());

  void end();
  // end name convention matching vk::CommandBuffer

 private:
  vk::CommandBuffer buffer_;
  vk::Fence fence_;
  vk::Device device_;

  void Initialize(vk::Device device, vk::CommandBuffer buffer);
  void Destroy();

  template <uint32_t N>
  friend class CommandBuffers;
};

template <uint32_t N>
class CommandBuffers {
 public:
  bool Initialize(vk::Device device, uint32_t graphics_family_queue_index) {
    device_ = device;
    command_pool_ = device_.createCommandPool(vk::CommandPoolCreateInfo(
        vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
        graphics_family_queue_index));

    auto cb = device_.allocateCommandBuffers(vk::CommandBufferAllocateInfo(
        command_pool_, vk::CommandBufferLevel::ePrimary, N));

    for (uint32_t i = 0; i < N; i++) {
      command_buffers_store_[i] = cb[i];
      command_buffers_[i].Initialize(device_, cb[i]);
    }
    return true;
  }

  void Destroy() {
    if (device_) {
      for (uint32_t i = 0; i < N; i++) {
        command_buffers_[i].Destroy();
      }
      device_.freeCommandBuffers(command_pool_, command_buffers_store_);
      device_.destroyCommandPool(command_pool_);
      device_ = VK_NULL_HANDLE;
    }
  }

  CommandBuffer& operator[](int i) {
    return command_buffers_[i];
  }

 private:
  std::array<vk::CommandBuffer, N> command_buffers_store_;
  std::array<CommandBuffer, N> command_buffers_;
  vk::CommandPool command_pool_;
  vk::Device device_;
};

}  // namespace Vulkan
}  // namespace ml
