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

#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1

#include "../include/app_framework/OpenXRCommon.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"
#include "../include/app_framework/XrMLGraphicsDeviceVulkan.h"
#ifdef XR_USE_PLATFORM_ANDROID
#include "../include/app_framework/vulkan/ImmutableYcbcrSampler.h"
#endif

using namespace ml;

XrMLGraphicsDeviceVulkan::XrMLGraphicsDeviceVulkan(XrCore *core)
    : core_(core),
      vulkan_enable_selected_(ENABLE1),
      vulkan_enable_(core_),
      vulkan_enable2_(core_),
      allocator_(VK_NULL_HANDLE) {
}

ml::XrMLGraphicsDeviceVulkan::~XrMLGraphicsDeviceVulkan() {
  views_.clear();
  DestroyCommandBuffers();
  DestroyDevice();
  DestroyInstance();
}

void XrMLGraphicsDeviceVulkan::PreInstanceInitialize(
    const std::vector<XrExtensionProperties> &extensions) {
  for (auto const &extension : extensions) {
    if (strcmp(extension.extensionName,
               Extensions::XrKHRVulkanEnable2::ExtensionName()) == 0) {
      vulkan_enable_selected_ = ENABLE2;
    }
  }
  ALOGI("XrCore using Vulkan, with vulkan enable %d", vulkan_enable_selected_);
}

bool XrMLGraphicsDeviceVulkan::Initialize() {
  try {
    switch (vulkan_enable_selected_) {
      case ENABLE1:
        if (!CreateInstance()) {
          return false;
        }
        if (!CreateDevice()) {
          return false;
        }
        break;
      case ENABLE2:
        if (!CreateInstance2()) {
          return false;
        }
        if (!CreateDevice2()) {
          return false;
        }
        break;
      default:
        throw std::runtime_error("not implemented.");
    }

    if (!CreateCommandBuffers()) {
      return false;
    }

  } catch (std::exception &e) {
    ALOGE("Failed to Initialize graphics device %s", e.what());
    return false;
  }

  return true;
}

void XrMLGraphicsDeviceVulkan::Finish() {
  WaitForFrameRenderFinished();
}

std::vector<const char *> XrMLGraphicsDeviceVulkan::RequiredExtensions() {
  switch (vulkan_enable_selected_) {
    case ENABLE1:
      return {Extensions::XrKHRVulkanEnable::ExtensionName()};
    case ENABLE2:
      return {Extensions::XrKHRVulkanEnable2::ExtensionName()};
    default:
      return {};
  }
}

void XrMLGraphicsDeviceVulkan::SetupViews(
    const std::vector<XrViewConfigurationView> &config_views,
    int64_t color_format, int64_t depth_format,
    uint32_t swap_chain_image_count) {
  if (config_views.empty()) {
    ALOGF("SetupViews needs config_views to have at least 1 element");
    return;
  }
  size_ = vk::Extent2D(config_views[0].recommendedImageRectWidth,
                       config_views[0].recommendedImageRectHeight);

  for (uint32_t i = 0; i < config_views.size(); i++) {
    View view{.render_pass = std::make_shared<Vulkan::RenderPass>(
                  device_, (vk::Format)color_format, (vk::Format)depth_format)};
    views_.push_back(view);
  }
}

std::pair<std::vector<XrSwapchainImageBaseHeader *>, ml::ISwapChainDataPtr>
XrMLGraphicsDeviceVulkan::AllocateSwapChainImageStructs(uint32_t count) {
  auto swap_chain = std::make_shared<Vulkan::SwapChain>(count);
  auto base_headers = swap_chain->GetSwapChainBaseHeaders();
  return {base_headers, swap_chain};
}

const XrBaseInStructure *XrMLGraphicsDeviceVulkan::GetGraphicsBindings() {
  return reinterpret_cast<XrBaseInStructure *>(&graphics_binding_);
}

VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
    void * /*pUserData*/) {
  ALOGE("Vulkan Error %s", pCallbackData->pMessage);
  return VK_FALSE;
}

bool XrMLGraphicsDeviceVulkan::CreateInstance() {
  std::vector<const char *> runtime_requested_extensions =
      vulkan_enable_.xrGetVulkanInstanceExtensionsKHR();
  XrGraphicsRequirementsVulkanKHR graphics_requirements =
      vulkan_enable_.xrGetVulkanGraphicsRequirementsKHR();

  ALOGI("Vulkan Min API = %d.%d, Max API = %d.%d",
        XR_VERSION_MAJOR(graphics_requirements.minApiVersionSupported),
        XR_VERSION_MINOR(graphics_requirements.minApiVersionSupported),
        XR_VERSION_MAJOR(graphics_requirements.maxApiVersionSupported),
        XR_VERSION_MINOR(graphics_requirements.maxApiVersionSupported));

  /* Setup the Vulkan loader */
  vk::DynamicLoader dl;
  PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
      dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
  VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);

  // Determine which layers to load
  std::vector<const char *> requested_layers = {"VK_LAYER_KHRONOS_validation"};
  std::vector<const char *> enabled_layers;
  /* Bind the instance */
  auto available_layer_properties = vk::enumerateInstanceLayerProperties();
  for (const auto requested_layer : requested_layers) {
    for (auto &prop : available_layer_properties) {
      ALOGI("Vulkan Layer: %s", prop.layerName.data());
      if (strcmp(prop.layerName.data(), requested_layer) == 0) {
        ALOGI("Enabling Vulkan Layer: %s", prop.layerName.data());
        enabled_layers.push_back(requested_layer);
      }
    }
  }

  // Determine which extensions to load
  auto available_extension_properties =
      vk::enumerateInstanceExtensionProperties();
  for (auto &prop : available_extension_properties) {
    ALOGI("Vulkan Extensions %s", prop.extensionName.data());
  }

  auto required_extensions =
      Merge(runtime_requested_extensions, {VK_EXT_DEBUG_UTILS_EXTENSION_NAME});

  for (const auto required_extension : required_extensions) {
    bool found = false;
    for (auto &prop : available_extension_properties) {
      if (strcmp(prop.extensionName.data(), required_extension) == 0) {
        found = true;
        break;
      }
    }
    if (!found) {
      ALOGE("Missing extension %s", required_extension);
      return false;
    }
  }

  for (auto ext : required_extensions) {
    ALOGI("Enabling Instance Extension: %s", ext);
  }

  vk::ApplicationInfo application_info(
      core_->AppName().c_str(), 1, "CAPI App Framework", 1, VK_API_VERSION_1_2);

  vk::InstanceCreateInfo create_info(
      {}, &application_info, static_cast<uint32_t>(enabled_layers.size()),
      enabled_layers.data(), static_cast<uint32_t>(required_extensions.size()),
      required_extensions.data());

  instance_ = vk::createInstance(create_info, nullptr);
  VULKAN_HPP_DEFAULT_DISPATCHER.init(instance_);

  /* Add debug information */

  vk::DebugUtilsMessengerCreateInfoEXT debug_create_info(
      {},
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
          vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
      vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
          vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
          vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
      &debugUtilsMessengerCallback, this);

  debug_utils_messenger_ =
      instance_.createDebugUtilsMessengerEXT(debug_create_info);

  physical_device_ = vulkan_enable_.xrGetVulkanGraphicsDeviceKHR(instance_);
  return true;
}

bool XrMLGraphicsDeviceVulkan::CreateInstance2() {
  XrGraphicsRequirementsVulkanKHR graphics_requirements =
      vulkan_enable2_.xrGetVulkanGraphicsRequirements2KHR();

  ALOGI("Vulkan Min API = %d.%d, Max API = %d.%d",
        XR_VERSION_MAJOR(graphics_requirements.minApiVersionSupported),
        XR_VERSION_MINOR(graphics_requirements.minApiVersionSupported),
        XR_VERSION_MAJOR(graphics_requirements.maxApiVersionSupported),
        XR_VERSION_MINOR(graphics_requirements.maxApiVersionSupported));

  /* Setup the Vulkan loader */
  vk::DynamicLoader dl;
  PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
      dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
  VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);

  // Determine which layers to load
  const char *VK_LAYER_KHRONOS_validation = "VK_LAYER_KHRONOS_validation";
  std::vector<const char *> requested_layers = {VK_LAYER_KHRONOS_validation};
  std::vector<const char *> enabled_layers;
  /* Bind the instance */
  auto available_layer_properties = vk::enumerateInstanceLayerProperties();
  for (const auto requested_layer : requested_layers) {
    for (auto &prop : available_layer_properties) {
      ALOGI("Vulkan Layer: %s", prop.layerName.data());
      if (strcmp(prop.layerName.data(), requested_layer) == 0) {
        ALOGI("Enabling Vulkan Layer: %s", prop.layerName.data());
        enabled_layers.push_back(requested_layer);
      }
    }
  }

  // Determine which extensions to load
  auto available_extension_properties =
      vk::enumerateInstanceExtensionProperties();
  for (auto &prop : available_extension_properties) {
    ALOGI("Vulkan Extensions %s", prop.extensionName.data());
  }

  std::vector<const char *> required_extensions = {
      VK_EXT_DEBUG_UTILS_EXTENSION_NAME};

  for (const auto required_extension : required_extensions) {
    bool found = false;
    for (auto &prop : available_extension_properties) {
      if (strcmp(prop.extensionName.data(), required_extension) == 0) {
        found = true;
        break;
      }
    }
    if (!found) {
      ALOGE("Missing extension %s", required_extension);
      return false;
    }
  }

  for (auto ext : required_extensions) {
    ALOGI("Enabling Instance Extension: %s", ext);
  }

  VkApplicationInfo application_info{
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext = nullptr,
      .pApplicationName = core_->AppName().c_str(),
      .applicationVersion = 1,
      .pEngineName = "CAPI App Framework",
      .apiVersion = VK_API_VERSION_1_2};

  VkInstanceCreateInfo vk_create_info{
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .pApplicationInfo = &application_info,
      .enabledLayerCount = static_cast<uint32_t>(enabled_layers.size()),
      .ppEnabledLayerNames = enabled_layers.data(),
      .enabledExtensionCount =
          static_cast<uint32_t>(required_extensions.size()),
      .ppEnabledExtensionNames = required_extensions.data()};

  XrVulkanInstanceCreateInfoKHR create_info{
      .type = XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR,
      .next = nullptr,
      .systemId = core_->SystemId(),
      .createFlags = 0,
      .pfnGetInstanceProcAddr = vkGetInstanceProcAddr,
      .vulkanCreateInfo = &vk_create_info,
      .vulkanAllocator = nullptr};

  VkResult result;
  instance_ = vulkan_enable2_.xrCreateVulkanInstanceKHR(&create_info, result);
  VULKAN_HPP_DEFAULT_DISPATCHER.init(instance_);

  /* Add debug information */

  vk::DebugUtilsMessengerCreateInfoEXT debug_create_info(
      {},
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
          vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
      vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
          vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
          vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
      &debugUtilsMessengerCallback, this);

  debug_utils_messenger_ =
      instance_.createDebugUtilsMessengerEXT(debug_create_info);

  physical_device_ = vulkan_enable2_.xrGetVulkanGraphicsDevice2KHR(instance_);

  return true;
}

void XrMLGraphicsDeviceVulkan::DestroyInstance() {
  if (debug_utils_messenger_) {
    instance_.destroy(debug_utils_messenger_);
  }
  if (instance_) {
    instance_.destroy();
  }
}

bool XrMLGraphicsDeviceVulkan::CreateDevice() {
  // Find all extensions the runtime needs.
  const auto runtime_requested_extensions =
      vulkan_enable_.xrGetVulkanDeviceExtensionsKHR();
  const auto required_extensions = Merge(
      runtime_requested_extensions,
      {
#ifdef XR_USE_PLATFORM_ANDROID
          VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME,
          VK_EXT_QUEUE_FAMILY_FOREIGN_EXTENSION_NAME
#endif
      });
  for (auto ext : required_extensions) {
    ALOGI("Runtime requested device extension: %s", ext);
  }

  std::vector<vk::QueueFamilyProperties> queue_family_properties =
      physical_device_.getQueueFamilyProperties();

  auto propertyIterator = std::find_if(
      queue_family_properties.begin(), queue_family_properties.end(),
      [](vk::QueueFamilyProperties const &qfp) {
        return qfp.queueFlags & vk::QueueFlagBits::eGraphics;
      });
  size_t graphics_queue_family_index =
      std::distance(queue_family_properties.begin(), propertyIterator);
  if (graphics_queue_family_index >= queue_family_properties.size()) {
    ALOGE("Could not find a graphics device");
    return false;
  }
  graphics_family_queue_index_ = (uint32_t)graphics_queue_family_index;

  float queue_priority = 0.0f;
  vk::DeviceQueueCreateInfo device_queue_create_info(
      vk::DeviceQueueCreateFlags(), graphics_family_queue_index_, 1,
      &queue_priority);

  vk::PhysicalDeviceFeatures features{};
  features.fillModeNonSolid = true;
  vk::PhysicalDeviceVulkan11Features features_11{};
#ifdef XR_USE_PLATFORM_ANDROID
  features_11.samplerYcbcrConversion = true;
#endif

  vk::DeviceCreateInfo device_create_info(
      vk::DeviceCreateFlags(), 1, &device_queue_create_info, 0, nullptr,
      (uint32_t)required_extensions.size(), required_extensions.data(),
      &features);
  device_create_info.pNext = &features_11;
  device_ = physical_device_.createDevice(device_create_info);

  static VmaVulkanFunctions vulkanFunctions{
      .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
      .vkGetDeviceProcAddr = vkGetDeviceProcAddr};
  VmaAllocatorCreateInfo allocatorCreateInfo = {};
  allocatorCreateInfo.vulkanApiVersion = VK_API_VERSION_1_2;
  allocatorCreateInfo.physicalDevice = physical_device_;
  allocatorCreateInfo.device = device_;
  allocatorCreateInfo.instance = instance_;
  allocatorCreateInfo.pVulkanFunctions = &vulkanFunctions;
  allocator_ = VK_NULL_HANDLE;
  vmaCreateAllocator(&allocatorCreateInfo, &allocator_);

  graphics_binding_ = {
      .type = XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR,
      .next = nullptr,
      .instance = instance_,
      .physicalDevice = physical_device_,
      .device = device_,
      .queueFamilyIndex = device_queue_create_info.queueFamilyIndex,
      .queueIndex = 0};
  queue_ = device_.getQueue(device_queue_create_info.queueFamilyIndex, 0);
  fence_ = device_.createFence({});

#ifdef XR_USE_PLATFORM_ANDROID
  Vulkan::ImmutableYcbcrSampler::GetInstance()->Initialize(device_);
#endif
  return true;
}

bool XrMLGraphicsDeviceVulkan::CreateDevice2() {
  // Find all extensions the runtime needs.
  const std::vector<const char *> required_extensions = {
#ifdef XR_USE_PLATFORM_ANDROID
      VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME,
      VK_EXT_QUEUE_FAMILY_FOREIGN_EXTENSION_NAME
#endif
  };

  for (auto ext : required_extensions) {
    ALOGI("Required device extension: %s", ext);
  }

  std::vector<vk::QueueFamilyProperties> queue_family_properties =
      physical_device_.getQueueFamilyProperties();

  auto propertyIterator = std::find_if(
      queue_family_properties.begin(), queue_family_properties.end(),
      [](vk::QueueFamilyProperties const &qfp) {
        return qfp.queueFlags & vk::QueueFlagBits::eGraphics;
      });
  size_t graphics_queue_family_index =
      std::distance(queue_family_properties.begin(), propertyIterator);
  if (graphics_queue_family_index >= queue_family_properties.size()) {
    ALOGE("Could not find a graphics device");
    return false;
  }
  graphics_family_queue_index_ = (uint32_t)graphics_queue_family_index;

  float queue_priority = 0.0f;
  VkDeviceQueueCreateInfo device_queue_create_info{
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = graphics_family_queue_index_,
      .queueCount = 1,
      .pQueuePriorities = &queue_priority};

  VkPhysicalDeviceFeatures features{};
  features.fillModeNonSolid = true;

  vk::PhysicalDeviceVulkan11Features features_11{};
#ifdef XR_USE_PLATFORM_ANDROID
  features_11.samplerYcbcrConversion = true;
#endif

  VkDeviceCreateInfo vk_device_create_info{
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .pNext = &features_11,
      .flags = 0,
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &device_queue_create_info,
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
      .enabledExtensionCount =
          static_cast<uint32_t>(required_extensions.size()),
      .ppEnabledExtensionNames = required_extensions.data(),
      .pEnabledFeatures = &features};

  XrVulkanDeviceCreateInfoKHR create_info{
      .type = XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR,
      .next = nullptr,
      .systemId = core_->SystemId(),
      .createFlags = 0,
      .pfnGetInstanceProcAddr = vkGetInstanceProcAddr,
      .vulkanPhysicalDevice = physical_device_,
      .vulkanCreateInfo = &vk_device_create_info,
      .vulkanAllocator = nullptr};

  VkResult vk_result;
  device_ = vulkan_enable2_.xrCreateVulkanDeviceKHR(&create_info, vk_result);
  if (vk_result != VK_SUCCESS) {
    throw std::runtime_error("Unable to create vulkan device");
  }

  static VmaVulkanFunctions vulkanFunctions{
      .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
      .vkGetDeviceProcAddr = vkGetDeviceProcAddr};
  VmaAllocatorCreateInfo allocatorCreateInfo = {};
  allocatorCreateInfo.vulkanApiVersion = VK_API_VERSION_1_2;
  allocatorCreateInfo.physicalDevice = physical_device_;
  allocatorCreateInfo.device = device_;
  allocatorCreateInfo.instance = instance_;
  allocatorCreateInfo.pVulkanFunctions = &vulkanFunctions;
  allocator_ = VK_NULL_HANDLE;
  vmaCreateAllocator(&allocatorCreateInfo, &allocator_);

  graphics_binding_ = {
      .type = XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR,
      .next = nullptr,
      .instance = instance_,
      .physicalDevice = physical_device_,
      .device = device_,
      .queueFamilyIndex = device_queue_create_info.queueFamilyIndex,
      .queueIndex = 0};
  queue_ = device_.getQueue(device_queue_create_info.queueFamilyIndex, 0);
  fence_ = device_.createFence({});

#ifdef XR_USE_PLATFORM_ANDROID
  Vulkan::ImmutableYcbcrSampler::GetInstance()->Initialize(device_);
#endif
  return true;
}

void XrMLGraphicsDeviceVulkan::DestroyDevice() {
  views_.clear();

#ifdef XR_USE_PLATFORM_ANDROID
  Vulkan::ImmutableYcbcrSampler::GetInstance()->Destroy(device_);
#endif
  if (fence_) {
    device_.destroy(fence_);
  }
  if (allocator_ != VK_NULL_HANDLE) {
    vmaDestroyAllocator(allocator_);
  }
  if (device_) {
    device_.destroy();
  }
}

int64_t XrMLGraphicsDeviceVulkan::SelectSwapChainGraphicsFormat(
    const std::vector<int64_t> &available) {
  const std::array<int64_t, 4> supported_color_swap_chain_formats{
      VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM,
      VK_FORMAT_B8G8R8A8_SRGB, VK_FORMAT_R8G8B8A8_SRGB};

  auto swap_chain_format_it =
      std::find_first_of(available.begin(), available.end(),
                         supported_color_swap_chain_formats.begin(),
                         supported_color_swap_chain_formats.end());
  if (swap_chain_format_it == available.end()) {
    ALOGE("No suitable color swapchain format available");
    return -1;
  }

  return *swap_chain_format_it;
}

int64_t XrMLGraphicsDeviceVulkan::SelectDepthSwapChainGraphicsFormat(
    const std::vector<int64_t> &available) {
  const std::array<int64_t, 2> supported_color_swap_chain_formats{
      VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT};

  auto swap_chain_format_it =
      std::find_first_of(available.begin(), available.end(),
                         supported_color_swap_chain_formats.begin(),
                         supported_color_swap_chain_formats.end());
  if (swap_chain_format_it == available.end()) {
    ALOGE("No suitable depth swapchain format available");
    return -1;
  }

  return *swap_chain_format_it;
}

std::vector<const char *> XrMLGraphicsDeviceVulkan::Merge(
    const std::vector<const char *> &list_a,
    const std::vector<const char *> &list_b) {
  std::vector<const char *> result;

  std::copy(list_a.begin(), list_a.end(), std::back_inserter(result));

  std::copy_if(list_b.begin(), list_b.end(), std::back_inserter(result),
               [result](const char *b) -> bool {
                 return std::find_if(result.begin(), result.end(),
                                     [b](const char *a) -> bool {
                                       return strcmp(a, b) == 0;
                                     }) == result.end();
               });

  return result;
}
bool XrMLGraphicsDeviceVulkan::CreateCommandBuffers() {
  return command_buffers_.Initialize(device_, graphics_family_queue_index_);
}

void XrMLGraphicsDeviceVulkan::DestroyCommandBuffers() {
  command_buffers_.Destroy();
}

vk::Queue &XrMLGraphicsDeviceVulkan::GetQueue() {
  return queue_;
}

void XrMLGraphicsDeviceVulkan::BindRenderPass(
    uint32_t view_index, const XrMLSwapChain *color_swap_chain,
    const XrMLSwapChain *depth_swap_chain,
    vk::RenderPassBeginInfo &renderPassBeginInfo) {
  const XrSwapchainImageVulkan2KHR *color_swi =
      reinterpret_cast<const XrSwapchainImageVulkan2KHR *>(
          color_swap_chain->GetSwapChainBaseHeader());
  const XrSwapchainImageVulkan2KHR *depth_swi =
      reinterpret_cast<const XrSwapchainImageVulkan2KHR *>(
          depth_swap_chain->GetSwapChainBaseHeader());

  assert(color_swi != nullptr);
  assert(depth_swi != nullptr);

  auto &view = views_[view_index];
  auto render_pass = view.render_pass.get();
  Vulkan::RenderTarget *render_target;

  uint32_t render_target_key =
      ((depth_swap_chain->AcquiredSwapChainIndex() & 0xffff) << 16) |
      (color_swap_chain->AcquiredSwapChainIndex() & 0xffff);
  auto render_target_it = view.render_targets.find(render_target_key);
  if (render_target_it == view.render_targets.end()) {
    auto render_target_ptr = std::make_shared<Vulkan::RenderTarget>(device_);
    view.render_targets[render_target_key] = render_target_ptr;
    render_target = render_target_ptr.get();
    render_target->Bind(color_swi->image, depth_swi->image, size_, render_pass);
  } else {
    render_target = render_target_it->second.get();
  }
  renderPassBeginInfo.renderPass = render_pass->Get();
  renderPassBeginInfo.framebuffer = render_target->GetFrameBuffer();
  renderPassBeginInfo.renderArea.offset.x = 0;
  renderPassBeginInfo.renderArea.offset.y = 0;
  renderPassBeginInfo.renderArea.extent = size_;
}
void XrMLGraphicsDeviceVulkan::WaitForFrameRenderFinished() {
  command_buffers_[0].wait(false);
  command_buffers_[1].wait(false);
}

#endif