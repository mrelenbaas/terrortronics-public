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

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include <map>
#include <mutex>

#include "Extensions/XrKHRVulkanEnable.h"
#include "Extensions/XrKHRVulkanEnable2.h"
#include "IXrMLGraphicsDevice.h"
#include "vulkan/CommandBuffers.h"
#include "vulkan/RenderPass.h"
#include "vulkan/RenderTarget.h"
#include "vulkan/SwapChain.h"

namespace ml {

class XrMLGraphicsDeviceVulkan : public IXrMLGraphicsDevice {
 public:
  XrMLGraphicsDeviceVulkan(XrCore *core);
  ~XrMLGraphicsDeviceVulkan();
  virtual void PreInstanceInitialize(
      const std::vector<XrExtensionProperties> &extensions) override;
  virtual bool Initialize() override;
  virtual std::vector<const char *> RequiredExtensions() override;
  virtual void Finish() override;
  virtual void SetupViews(
      const std::vector<XrViewConfigurationView> &config_views,
      int64_t color_format, int64_t depth_format,
      uint32_t swap_chain_image_count) override;
  std::pair<std::vector<XrSwapchainImageBaseHeader *>, ml::ISwapChainDataPtr>
  AllocateSwapChainImageStructs(uint32_t count) override;
  virtual const XrBaseInStructure *GetGraphicsBindings() override;
  virtual int64_t SelectSwapChainGraphicsFormat(
      const std::vector<int64_t> &available) override;
  virtual int64_t SelectDepthSwapChainGraphicsFormat(
      const std::vector<int64_t> &available) override;
  vk::Queue &GetQueue();

  void WaitForFrameRenderFinished() override;

 protected:
  bool CreateInstance();
  bool CreateInstance2();
  void DestroyInstance();

  bool CreateDevice();
  bool CreateDevice2();
  void DestroyDevice();

  bool CreateCommandBuffers();
  void DestroyCommandBuffers();

  void BindRenderPass(uint32_t view_index,
                      const XrMLSwapChain *color_swap_chain,
                      const XrMLSwapChain *depth_swap_chain,
                      vk::RenderPassBeginInfo &renderPassBeginInfo);

  static std::vector<const char *> Merge(
      const std::vector<const char *> &list_a,
      const std::vector<const char *> &list_b);

  XrCore *core_;
  enum VulkanEnable { ENABLE1 = 1, ENABLE2 };
  VulkanEnable vulkan_enable_selected_;
  Extensions::XrKHRVulkanEnable vulkan_enable_;
  Extensions::XrKHRVulkanEnable2 vulkan_enable2_;
  vk::Instance instance_;
  vk::DebugUtilsMessengerEXT debug_utils_messenger_;
  vk::PhysicalDevice physical_device_;
  vk::Device device_;
  vk::Queue queue_;
  vk::Fence fence_;
  XrGraphicsBindingVulkanKHR graphics_binding_;
  uint32_t graphics_family_queue_index_;
  vk::CommandPool command_pool_;
  Vulkan::CommandBuffers<2> command_buffers_;
  VmaAllocator allocator_;
  vk::Extent2D size_;

  struct View {
    std::shared_ptr<Vulkan::RenderPass> render_pass;
    std::map<uint32_t, std::shared_ptr<Vulkan::RenderTarget>> render_targets;
  };
  std::vector<View> views_;
};

}  // namespace ml

#endif
