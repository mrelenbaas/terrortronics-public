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

#ifdef XR_USE_PLATFORM_ANDROID
#include "../include/app_framework/vulkan/NativeImageBuffer.h"

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/vulkan/AndroidHwBufferHelper.h"
#include "../include/app_framework/vulkan/ImmutableYcbcrSampler.h"

using namespace ml::Vulkan;

NativeImageBuffer::NativeImageBuffer(XrCore *core,
                                     vk::PhysicalDevice phys_device,
                                     vk::Device device, VmaAllocator allocator)
    : ImageBuffer(core, phys_device, device, allocator) {
}

NativeImageBuffer::~NativeImageBuffer() {
  Release();
}

void NativeImageBuffer::Release() {
  if (image_) {
    device_.destroyImage(image_, nullptr);
    image_ = VK_NULL_HANDLE;
    vkFreeMemory(device_, device_memory_, nullptr);
    device_memory_ = VK_NULL_HANDLE;
  }

  if (image_view_) {
    device_.destroyImageView(image_view_);
    image_view_ = nullptr;
  }
}

bool NativeImageBuffer::UpdateTextureImage(
    ml::Vulkan::CommandBuffer &command_buffer, vk::Queue &queue,
    AHardwareBuffer *buffer, uint32_t width, uint32_t height) {
  Release();

  width_ = width;
  height_ = height;
  const auto res = AndroidHwBufferHelper::CreateTextureImage(
      buffer, width, height, device_, &image_, &device_memory_, &format_);
  if (res) {
    image_layout_ = vk::ImageLayout::eUndefined;
    Transition(command_buffer, queue, image_layout_,
               vk::ImageLayout::eShaderReadOnlyOptimal);

    CreateImageView(vk::ImageAspectFlagBits::eColor);
  }
  return res;
}

void NativeImageBuffer::TieWithTexture(Components::ITexturePtr tex) {
  src_texture_ = tex;
}

void NativeImageBuffer::CreateImageView(vk::ImageAspectFlags aspect_flags,
                                        uint32_t levels) {
  const auto sampler_conversion_info =
      ImmutableYcbcrSampler::GetInstance()->GetSamplerConversionInfo();
  vk::ImageViewCreateInfo view_info(
      {}, image_, vk::ImageViewType::e2D, format_, {},
      {aspect_flags, 0, levels, 0, 1},
      (VkSamplerYcbcrConversionInfo *)&sampler_conversion_info);
  image_view_ = device_.createImageView(view_info);
}

void NativeImageBuffer::CreateSampler(const ITexture::ShaderSettings &) {
  // Sampler is useless here because we use pImmutableSampler in
  // DescriptorSetLayout
  image_sampler_ = nullptr;
}

bool NativeImageBuffer::PreRenderUpdate(
    ml::Vulkan::CommandBuffer &command_buffer, vk::Queue &queue) {
  auto tex = GetTexture();
  tex->Close();
  if (tex->Open()) {
    UpdateTextureImage(command_buffer, queue, (AHardwareBuffer *)tex->Data(),
                       tex->Width(), tex->Height());
    return true;
  }

  return false;
}

#endif