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

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include <string>
#include <vector>

namespace ml {
class XrCore;
}  // namespace ml

namespace ml::Extensions {

class XrKHRVulkanEnable2 {
 public:
  XrKHRVulkanEnable2(XrCore *core);

  // no copy or assigning please.
  XrKHRVulkanEnable2(const XrKHRVulkanEnable2 &) = delete;
  XrKHRVulkanEnable2 &operator=(XrKHRVulkanEnable2 const &) = delete;

  XrGraphicsRequirementsVulkanKHR xrGetVulkanGraphicsRequirements2KHR();
  vk::PhysicalDevice xrGetVulkanGraphicsDevice2KHR(vk::Instance instance);
  vk::Instance xrCreateVulkanInstanceKHR(
      const XrVulkanInstanceCreateInfoKHR *create_info, VkResult &result);
  vk::Device xrCreateVulkanDeviceKHR(
      const XrVulkanDeviceCreateInfoKHR *create_info, VkResult &result);
  static const char *ExtensionName();

 private:
  XrCore *core_;
};

}  // namespace ml::Extensions

#endif