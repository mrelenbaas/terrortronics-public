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

#include "../IXrMLGraphicsDevice.h"
#include "../OpenXRCommon.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

namespace ml {
namespace Vulkan {
class SwapChain : public ml::ISwapChainData {
 public:
  SwapChain(uint32_t capacity);

  // no copy or assigning please.
  SwapChain(const SwapChain &) = delete;
  SwapChain &operator=(SwapChain const &) = delete;

  inline std::vector<XrSwapchainImageBaseHeader *> GetSwapChainBaseHeaders() {
    return bases_;
  }

 private:
  std::vector<XrSwapchainImageBaseHeader *> bases_;
  std::vector<XrSwapchainImageVulkan2KHR> swap_chain_images_;
};
}  // namespace Vulkan
}  // namespace ml

#endif