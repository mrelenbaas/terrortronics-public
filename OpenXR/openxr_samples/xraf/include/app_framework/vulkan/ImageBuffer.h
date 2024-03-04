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

#include "../Components/Component.h"
#include "../Components/ITexture.h"
#include "../Logging.h"
#include "../OpenXRCommon.h"
#include "../XrCore.h"
#include "Buffer.h"
#include "CommandBuffers.h"
#include "TextureDescriptorPool.h"

namespace ml {

namespace Vulkan {

class ImageBuffer : public ml::Components::IComponent {
  inline uint32_t DescriptorMapKey(
      ml::Components::Material::TextureType texture_type,
      ml::Vulkan::TextureDescriptorPool::PipelineLayoutType
          pipeline_layout_type) const {
    uint32_t value =
        (texture_type & 0xffff) | ((pipeline_layout_type & 0xffff) << 16);
    return value;
  }

 public:
  ImageBuffer(XrCore *core_, vk::PhysicalDevice phys_device, vk::Device device,
              VmaAllocator allocator);
  ~ImageBuffer();

  ImageBuffer(const ImageBuffer &) = delete;
  ImageBuffer &operator=(const ImageBuffer &) = delete;
  ImageBuffer(ImageBuffer &&source) = delete;
  ImageBuffer &operator=(ImageBuffer &&source) = delete;

  // Create from encoded image PNG/JPG/etc...
  void CreateTextureImage(ml::Vulkan::CommandBuffer &command_buffer,
                          vk::Queue &queue, const char *data, size_t size,
                          vk::Format format,
                          const ITexture::ShaderSettings &shader_settings);

  // Create from 4 byte RGBA per pixel image using specified format.
  // images should use vk::Format::eR8G8B8A8Srgb
  // normal maps should use vk::Format::eR8G8B8A8Unorm
  void CreateTextureImage(ml::Vulkan::CommandBuffer &command_buffer,
                          vk::Queue &queue, const char *data, uint32_t width,
                          uint32_t height, vk::Format format,
                          const ITexture::ShaderSettings &shader_settings);

  // Create empty image
  void CreateTextureImage(
      ml::Vulkan::CommandBuffer &command_buffer, vk::Queue &queue,
      uint32_t width, uint32_t height,
      vk::ImageUsageFlags usage = vk::ImageUsageFlagBits::eSampled |
                                  vk::ImageUsageFlagBits::eTransferDst);

  vk::DescriptorImageInfo DescriptorImageInfo() {
    return vk::DescriptorImageInfo{
        image_sampler_,
        image_view_,
        image_layout_,
    };
  }

  void CreateDepthImage(ml::Vulkan::CommandBuffer &command_buffer,
                        vk::Queue &queue, uint32_t width, uint32_t height);

  vk::Format Format() const {
    return format_;
  }

  vk::Image Image() const {
    return image_;
  }

  vk::ImageView ImageView() const {
    return image_view_;
  };

  uint32_t Width() const {
    return width_;
  }

  uint32_t Height() const {
    return height_;
  }

  void OverrideImageLayout(vk::ImageLayout layout) {
    image_layout_ = layout;
  }

  // Perform any updates that may change the Image. Return true if related
  // DescriptorSet should be updated.
  virtual bool PreRenderUpdate(ml::Vulkan::CommandBuffer &command_buffer,
                               vk::Queue &queue) {
    return false;
  }

 protected:
  XrCore *core_;
  vk::PhysicalDevice phys_device_;
  vk::Device device_;
  VmaAllocator allocator_;

  vk::Image image_;
  vk::Format format_;
  VmaAllocation allocation_;
  vk::ImageView image_view_;
  vk::Sampler image_sampler_;
  vk::ImageLayout image_layout_;

  uint32_t width_;
  uint32_t height_;

  void InsertImageMemoryBarrier(ml::Vulkan::CommandBuffer &command_buffer,
                                vk::Image image,
                                vk::AccessFlags src_access_mask,
                                vk::AccessFlags dst_access_mask,
                                vk::ImageLayout old_image_layout,
                                vk::ImageLayout new_image_layout,
                                vk::PipelineStageFlags src_stage_mask,
                                vk::PipelineStageFlags dst_stage_mask,
                                vk::ImageSubresourceRange subresource_range);
  void FlushCommandBuffer(ml::Vulkan::CommandBuffer &command_buffer,
                          vk::Queue queue);

  void CreateImage(uint32_t width, uint32_t height, vk::Format format,
                   vk::ImageTiling tiling, vk::ImageUsageFlags usage,
                   int mip_levels);
  void Transition(ml::Vulkan::CommandBuffer &command_buffer, vk::Queue &queue,
                  vk::ImageLayout old_layout, vk::ImageLayout new_layout);
  void CopyImage(ml::Vulkan::CommandBuffer &command_buffer, vk::Queue &queue,
                 vk::Buffer buffer, uint32_t width, uint32_t height);

  virtual void CreateImageView(vk::ImageAspectFlags aspect_flags,
                               uint32_t levels = 1);
  virtual void CreateSampler(const ITexture::ShaderSettings &shader_settings =
                                 ITexture::ShaderSettings{});
  vk::Format FindSupportedFormat(const std::vector<vk::Format> &candidates,
                                 vk::ImageTiling tiling,
                                 vk::FormatFeatureFlags features);
  vk::Format FindDepthFormat();
  bool HasStencilComponent(vk::Format format) {
    return format == vk::Format::eD32SfloatS8Uint ||
           format == vk::Format::eD24UnormS8Uint;
  }

  uint32_t GetMipmapLevels(uint32_t width, uint32_t height,
                           vk::Format format) const;
  void GenerateMipmaps(ml::Vulkan::CommandBuffer &command_buffer,
                       vk::Queue &queue, uint32_t width, uint32_t height,
                       uint32_t mipmap_levels);
};

using ImageBufferPtr = std::shared_ptr<ImageBuffer>;
using ImageBufferWeakPtr = std::weak_ptr<ImageBuffer>;

}  // namespace Vulkan
}  // namespace ml
