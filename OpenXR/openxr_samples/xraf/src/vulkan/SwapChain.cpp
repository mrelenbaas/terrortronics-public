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

#include "../include/app_framework/vulkan/SwapChain.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

using namespace ml::Vulkan;

SwapChain::SwapChain(uint32_t capacity) {
  swap_chain_images_.reserve(capacity);
  bases_.reserve(capacity);
  for (uint32_t i = 0; i < capacity; ++i) {
    swap_chain_images_.push_back({.type = XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR});
    bases_.push_back(reinterpret_cast<XrSwapchainImageBaseHeader *>(
        &swap_chain_images_.back()));
  }
}

#endif