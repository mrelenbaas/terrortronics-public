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

#include "../include/app_framework/vulkan/ImageBuffer.h"

#ifdef XR_USE_PLATFORM_ANDROID
struct AHardwareBuffer;

namespace ml {
namespace Vulkan {

class NativeImageBuffer : public ImageBuffer {
 public:
  NativeImageBuffer(XrCore *core_, vk::PhysicalDevice phys_device,
                    vk::Device device, VmaAllocator allocator);
  ~NativeImageBuffer();

  NativeImageBuffer(const NativeImageBuffer &) = delete;
  NativeImageBuffer &operator=(const NativeImageBuffer &) = delete;
  NativeImageBuffer(NativeImageBuffer &&source) = delete;
  NativeImageBuffer &operator=(NativeImageBuffer &&source) = delete;

  // Update held VkImage from given AHardwareBuffer, update VkImageView and
  // VkSampler as well.
  bool UpdateTextureImage(ml::Vulkan::CommandBuffer &command_buffer,
                          vk::Queue &queue, AHardwareBuffer *ahardwarebuffer,
                          uint32_t width, uint32_t height);

  // Store texture pointer.
  void TieWithTexture(Components::ITexturePtr tex);

  inline ml::Components::ITexturePtr GetTexture() const {
    return src_texture_;
  }

  bool PreRenderUpdate(ml::Vulkan::CommandBuffer &command_buffer,
                       vk::Queue &queue) override;

 protected:
  vk::DeviceMemory device_memory_;
  Components::ITexturePtr src_texture_;

  void Release();
  void CreateImageView(vk::ImageAspectFlags aspect_flags,
                       uint32_t levels = 1) override;
  void CreateSampler(
      const ITexture::ShaderSettings & = ITexture::ShaderSettings{}) override;
};

}  // namespace Vulkan
}  // namespace ml
#endif