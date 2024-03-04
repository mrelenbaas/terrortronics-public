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

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../include/app_framework/Extensions/XrKHRVulkanEnable.h"

#include <sstream>
#include <string>
#include <vector>

#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

XrKHRVulkanEnable::XrKHRVulkanEnable(XrCore *core) : core_(core) {
}

std::vector<const char *>
XrKHRVulkanEnable::xrGetVulkanInstanceExtensionsKHR() {
  PFN_xrGetVulkanInstanceExtensionsKHR xrGetVulkanInstanceExtensionsKHR =
      nullptr;
  if (xrGetInstanceProcAddr(
          core_->Instance(), "xrGetVulkanInstanceExtensionsKHR",
          reinterpret_cast<PFN_xrVoidFunction *>(
              &xrGetVulkanInstanceExtensionsKHR)) != XR_SUCCESS) {
    throw std::runtime_error(
        "xrGetVulkanInstanceExtensionsKHR cannot be found");
  }
  uint32_t count;
  if (xrGetVulkanInstanceExtensionsKHR(core_->Instance(), core_->SystemId(), 0,
                                       &count, nullptr) != XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanInstanceExtensionsKHR failed");
  }
  if (count > 0) {
    std::vector<char> names(count);
    if (xrGetVulkanInstanceExtensionsKHR(core_->Instance(), core_->SystemId(),
                                         count, &count,
                                         names.data()) != XR_SUCCESS) {
      throw std::runtime_error("xrGetVulkanInstanceExtensionsKHR failed");
    }
    return StringSplit(names.data());
  }
  return {};
}

std::vector<const char *> XrKHRVulkanEnable::xrGetVulkanDeviceExtensionsKHR() {
  PFN_xrGetVulkanDeviceExtensionsKHR xrGetVulkanDeviceExtensionsKHR = nullptr;
  if (xrGetInstanceProcAddr(core_->Instance(), "xrGetVulkanDeviceExtensionsKHR",
                            reinterpret_cast<PFN_xrVoidFunction *>(
                                &xrGetVulkanDeviceExtensionsKHR)) !=
      XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanDeviceExtensionsKHR cannot be found");
  }

  uint32_t count;
  if (xrGetVulkanDeviceExtensionsKHR(core_->Instance(), core_->SystemId(), 0,
                                     &count, nullptr) != XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanDeviceExtensionsKHR failed");
  }
  if (count > 0) {
    std::vector<char> names(count);
    if (xrGetVulkanDeviceExtensionsKHR(core_->Instance(), core_->SystemId(),
                                       count, &count,
                                       names.data()) != XR_SUCCESS) {
      throw std::runtime_error("xrGetVulkanDeviceExtensionsKHR failed");
    }
    return StringSplit(names.data());
  }
  return {};
}

XrGraphicsRequirementsVulkanKHR
XrKHRVulkanEnable::xrGetVulkanGraphicsRequirementsKHR() {
  PFN_xrGetVulkanGraphicsRequirementsKHR xrGetVulkanGraphicsRequirementsKHR =
      nullptr;
  if (xrGetInstanceProcAddr(
          core_->Instance(), "xrGetVulkanGraphicsRequirementsKHR",
          reinterpret_cast<PFN_xrVoidFunction *>(
              &xrGetVulkanGraphicsRequirementsKHR)) != XR_SUCCESS) {
    throw std::runtime_error(
        "xrGetVulkanGraphicsRequirementsKHR cannot be found");
  }

  XrGraphicsRequirementsVulkanKHR graphics_requirements{
      .type = XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR, .next = nullptr};
  if (xrGetVulkanGraphicsRequirementsKHR(core_->Instance(), core_->SystemId(),
                                         &graphics_requirements) !=
      XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanGraphicsRequirementsKHR failed");
  }
  return graphics_requirements;
}

vk::PhysicalDevice XrKHRVulkanEnable::xrGetVulkanGraphicsDeviceKHR(
    vk::Instance instance) {
  PFN_xrGetVulkanGraphicsDeviceKHR xrGetVulkanGraphicsDeviceKHR = nullptr;
  if (xrGetInstanceProcAddr(core_->Instance(), "xrGetVulkanGraphicsDeviceKHR",
                            reinterpret_cast<PFN_xrVoidFunction *>(
                                &xrGetVulkanGraphicsDeviceKHR)) != XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanGraphicsDeviceKHR cannot be found");
  }

  VkPhysicalDevice physical_device;
  if (xrGetVulkanGraphicsDeviceKHR(core_->Instance(), core_->SystemId(),
                                   instance, &physical_device) != XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanGraphicsDeviceKHR failed");
  }
  return physical_device;
}

std::vector<const char *> XrKHRVulkanEnable::StringSplit(const char *names) {
  std::stringstream name_stream(names);
  names_.clear();
  {
    std::string name;
    while (std::getline(name_stream, name, ' ')) {
      names_.push_back(name);
    }
  }

  std::vector<const char *> list;
  for (const auto &name : names_) {
    list.push_back(name.c_str());
  }
  return list;
}

const char *XrKHRVulkanEnable::ExtensionName() {
  static const char *name = XR_KHR_VULKAN_ENABLE_EXTENSION_NAME;
  return name;
}

#endif
