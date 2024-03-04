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

#include "../../include/app_framework/vulkan/CommandBuffers.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

using namespace ml::Vulkan;

#include "../include/app_framework/Logging.h"

void CommandBuffer::wait(bool reset) {
  auto r = device_.waitForFences(1, &fence_, true, UINT64_MAX);
  if (r != vk::Result::eSuccess) {
    ALOGE("Wait For Fence failed. %d", r);
  }
  if (!reset) {
    return;
  }
  r = device_.resetFences(1, &fence_);
  if (r != vk::Result::eSuccess) {
    ALOGE("Reset Fence Failed. %d", r);
  }
}

void CommandBuffer::reset() {
  buffer_.reset();
}

void CommandBuffer::begin(const vk::CommandBufferBeginInfo &beginInfo) {
  buffer_.begin(beginInfo);
}

void CommandBuffer::end() {
  buffer_.end();
}

void CommandBuffer::Initialize(vk::Device device, vk::CommandBuffer buffer) {
  device_ = device;
  vk::FenceCreateInfo fence_create_info;
  fence_create_info.flags = vk::FenceCreateFlagBits::eSignaled;
  fence_ = device.createFence(fence_create_info);
  buffer_ = buffer;
}

void CommandBuffer::Destroy() {
  if (fence_) {
    device_.destroy(fence_);
    fence_ = VK_NULL_HANDLE;
  }
}

#endif
