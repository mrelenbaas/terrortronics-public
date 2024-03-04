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

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../include/app_framework/Extensions/XrKHRVulkanEnable2.h"

#include <sstream>
#include <string>
#include <vector>

#include "../include/app_framework/XrCore.h"

using namespace ml::Extensions;

XrKHRVulkanEnable2::XrKHRVulkanEnable2(XrCore *core) : core_(core) {
}

XrGraphicsRequirementsVulkanKHR
XrKHRVulkanEnable2::xrGetVulkanGraphicsRequirements2KHR() {
  PFN_xrGetVulkanGraphicsRequirements2KHR xrGetVulkanGraphicsRequirements2KHR =
      nullptr;
  if (xrGetInstanceProcAddr(
          core_->Instance(), "xrGetVulkanGraphicsRequirements2KHR",
          reinterpret_cast<PFN_xrVoidFunction *>(
              &xrGetVulkanGraphicsRequirements2KHR)) != XR_SUCCESS) {
    throw std::runtime_error(
        "xrGetVulkanGraphicsRequirements2KHR cannot be found");
  }

  XrGraphicsRequirementsVulkanKHR graphics_requirements{
      .type = XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR, .next = nullptr};
  if (xrGetVulkanGraphicsRequirements2KHR(core_->Instance(), core_->SystemId(),
                                          &graphics_requirements) !=
      XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanGraphicsRequirements2KHR failed");
  }
  return graphics_requirements;
}

vk::PhysicalDevice XrKHRVulkanEnable2::xrGetVulkanGraphicsDevice2KHR(
    vk::Instance instance) {
  PFN_xrGetVulkanGraphicsDevice2KHR xrGetVulkanGraphicsDevice2KHR = nullptr;
  if (xrGetInstanceProcAddr(core_->Instance(), "xrGetVulkanGraphicsDevice2KHR",
                            reinterpret_cast<PFN_xrVoidFunction *>(
                                &xrGetVulkanGraphicsDevice2KHR)) !=
      XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanGraphicsDevice2KHR cannot be found");
  }
  XrVulkanGraphicsDeviceGetInfoKHR get_info{
      XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR};
  get_info.systemId = core_->SystemId();
  get_info.vulkanInstance = instance;

  VkPhysicalDevice physical_device;
  if (xrGetVulkanGraphicsDevice2KHR(core_->Instance(), &get_info,
                                    &physical_device) != XR_SUCCESS) {
    throw std::runtime_error("xrGetVulkanGraphicsDevice2KHR failed");
  }
  return physical_device;
}

vk::Instance XrKHRVulkanEnable2::xrCreateVulkanInstanceKHR(
    const XrVulkanInstanceCreateInfoKHR *create_info, VkResult &result) {
  PFN_xrCreateVulkanInstanceKHR xrCreateVulkanInstanceKHR = nullptr;
  if (xrGetInstanceProcAddr(core_->Instance(), "xrCreateVulkanInstanceKHR",
                            reinterpret_cast<PFN_xrVoidFunction *>(
                                &xrCreateVulkanInstanceKHR)) != XR_SUCCESS) {
    throw std::runtime_error("xrCreateVulkanInstanceKHR cannot be found");
  }
  VkInstance vk_instance;
  if (xrCreateVulkanInstanceKHR(core_->Instance(), create_info, &vk_instance,
                                &result) != XR_SUCCESS) {
    throw std::runtime_error("xrCreateVulkanInstanceKHR failed");
  }
  return vk_instance;
}

vk::Device XrKHRVulkanEnable2::xrCreateVulkanDeviceKHR(
    const XrVulkanDeviceCreateInfoKHR *create_info, VkResult &result) {
  PFN_xrCreateVulkanDeviceKHR xrCreateVulkanDeviceKHR = nullptr;
  if (xrGetInstanceProcAddr(core_->Instance(), "xrCreateVulkanDeviceKHR",
                            reinterpret_cast<PFN_xrVoidFunction *>(
                                &xrCreateVulkanDeviceKHR)) != XR_SUCCESS) {
    throw std::runtime_error("xrCreateVulkanDeviceKHR cannot be found");
  }
  VkDevice vk_device;
  if (xrCreateVulkanDeviceKHR(core_->Instance(), create_info, &vk_device,
                              &result) != XR_SUCCESS) {
    throw std::runtime_error("xrCreateVulkanDeviceKHR failed");
  }
  return vk_device;
}

const char *XrKHRVulkanEnable2::ExtensionName() {
  static const char *name = XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME;
  return name;
}

#endif
