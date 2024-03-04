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

#include <string>
#include <vector>

namespace ml {
class XrCore;
}  // namespace ml

namespace ml::Extensions {

class XrKHRVulkanEnable {
 public:
  XrKHRVulkanEnable(XrCore *core);

  // no copy or assigning please.
  XrKHRVulkanEnable(const XrKHRVulkanEnable &) = delete;
  XrKHRVulkanEnable &operator=(XrKHRVulkanEnable const &) = delete;

  // returns instance extensions required.
  // strings valid until next call of xrGetVulkanInstanceExtensionsKHR
  // or xrGetVulkanDeviceExtensionsKHR
  std::vector<const char *> xrGetVulkanInstanceExtensionsKHR();
  std::vector<const char *> xrGetVulkanDeviceExtensionsKHR();
  XrGraphicsRequirementsVulkanKHR xrGetVulkanGraphicsRequirementsKHR();
  vk::PhysicalDevice xrGetVulkanGraphicsDeviceKHR(vk::Instance instance);
  static const char *ExtensionName();

 private:
  XrCore *core_;
  std::vector<std::string> names_;
  std::vector<const char *> StringSplit(const char *names);
};

}  // namespace ml::Extensions

#endif
