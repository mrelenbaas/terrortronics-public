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

#include "../include/app_framework/vulkan/ImageBuffer.h"

#include <stb_image.h>

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../include/app_framework/Logging.h"

using namespace ml::Vulkan;

ImageBuffer::ImageBuffer(XrCore *core, vk::PhysicalDevice phys_device,
                         vk::Device device, VmaAllocator allocator)
    : core_(core),
      phys_device_(phys_device),
      device_(device),
      allocator_(allocator),
      image_(VK_NULL_HANDLE),
      format_(vk::Format::eUndefined),
      allocation_(VK_NULL_HANDLE),
      image_view_(VK_NULL_HANDLE),
      image_sampler_(VK_NULL_HANDLE),
      image_layout_(vk::ImageLayout::eUndefined),
      width_(0),
      height_(0) {
}

ImageBuffer::~ImageBuffer() {
  if (allocation_ != VK_NULL_HANDLE) {
    vmaDestroyImage(allocator_, image_, allocation_);
    image_ = VK_NULL_HANDLE;
    allocation_ = VK_NULL_HANDLE;
  }

  if (image_sampler_) {
    device_.destroySampler(image_sampler_);
    image_sampler_ = nullptr;
  }

  if (image_view_) {
    device_.destroyImageView(image_view_);
    image_view_ = nullptr;
  }
}

uint32_t ImageBuffer::GetMipmapLevels(uint32_t width, uint32_t height,
                                      vk::Format format) const {
  uint32_t mipmap_levels = 1;
  vk::FormatProperties format_properties;
  phys_device_.getFormatProperties(format, &format_properties);
  if ((!(format_properties.optimalTilingFeatures &
         vk::FormatFeatureFlagBits::eBlitSrc)) ||
      (!(format_properties.optimalTilingFeatures &
         vk::FormatFeatureFlagBits::eBlitDst))) {
    ALOGE("Cannot generate mipmaps on GPU.");
    // Magic Leap 2 does support this.
    mipmap_levels = 0;
  } else {
    mipmap_levels = 0;
    int w = width;
    int h = height;
    const int min_size = 32;
    while ((w > min_size) && (h > min_size)) {
      mipmap_levels++;
      w = w >> 1;  // div 2
      h = h >> 1;  // div 2
    }
  }
  return mipmap_levels;
}

void ImageBuffer::GenerateMipmaps(ml::Vulkan::CommandBuffer &command_buffer,
                                  vk::Queue &queue, uint32_t width,
                                  uint32_t height, uint32_t mipmap_levels) {
  command_buffer.wait();
  command_buffer.reset();
  // Finish transition of original image
  command_buffer.begin(vk::CommandBufferBeginInfo{
      vk::CommandBufferUsageFlagBits::eOneTimeSubmit});

  vk::ImageSubresourceRange subresource_range = {};
  subresource_range.aspectMask = vk::ImageAspectFlagBits::eColor;
  subresource_range.levelCount = 1;
  subresource_range.layerCount = 1;

  InsertImageMemoryBarrier(
      command_buffer, image_, vk::AccessFlagBits::eTransferWrite,
      vk::AccessFlagBits::eTransferRead, vk::ImageLayout::eTransferDstOptimal,
      vk::ImageLayout::eTransferSrcOptimal,
      vk::PipelineStageFlagBits::eTransfer,
      vk::PipelineStageFlagBits::eTransfer, subresource_range);

  FlushCommandBuffer(command_buffer, queue);

  vk::CommandBuffer cb = command_buffer;
  command_buffer.wait();
  command_buffer.reset();
  command_buffer.begin(vk::CommandBufferBeginInfo{
      vk::CommandBufferUsageFlagBits::eOneTimeSubmit});

  for (uint32_t i = 1; i < mipmap_levels; i++) {
    vk::ImageBlit image_blit{};

    // Source
    image_blit.srcSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    image_blit.srcSubresource.layerCount = 1;
    image_blit.srcSubresource.mipLevel = i - 1;
    image_blit.srcOffsets[1].x = int32_t(width >> (i - 1));
    image_blit.srcOffsets[1].y = int32_t(height >> (i - 1));
    image_blit.srcOffsets[1].z = 1;

    // Destination
    image_blit.dstSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    image_blit.dstSubresource.layerCount = 1;
    image_blit.dstSubresource.mipLevel = i;
    image_blit.dstOffsets[1].x = int32_t(width >> i);
    image_blit.dstOffsets[1].y = int32_t(height >> i);
    image_blit.dstOffsets[1].z = 1;

    vk::ImageSubresourceRange mip_sub_range = {};
    mip_sub_range.aspectMask = vk::ImageAspectFlagBits::eColor;
    mip_sub_range.baseMipLevel = i;
    mip_sub_range.levelCount = 1;
    mip_sub_range.layerCount = 1;

    InsertImageMemoryBarrier(
        command_buffer, image_, {}, vk::AccessFlagBits::eTransferWrite,
        vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal,
        vk::PipelineStageFlagBits::eTransfer,
        vk::PipelineStageFlagBits::eTransfer, mip_sub_range);

    cb.blitImage(image_, vk::ImageLayout::eTransferSrcOptimal, image_,
                 vk::ImageLayout::eTransferDstOptimal, 1, &image_blit,
                 vk::Filter::eLinear);

    InsertImageMemoryBarrier(
        command_buffer, image_, vk::AccessFlagBits::eTransferWrite,
        vk::AccessFlagBits::eTransferRead, vk::ImageLayout::eTransferDstOptimal,
        vk::ImageLayout::eTransferSrcOptimal,
        vk::PipelineStageFlagBits::eTransfer,
        vk::PipelineStageFlagBits::eTransfer, mip_sub_range);
  }  // loop

  subresource_range.levelCount = mipmap_levels;
  InsertImageMemoryBarrier(
      command_buffer, image_, vk::AccessFlagBits::eTransferRead,
      vk::AccessFlagBits::eShaderRead, vk::ImageLayout::eTransferSrcOptimal,
      vk::ImageLayout::eShaderReadOnlyOptimal,
      vk::PipelineStageFlagBits::eTransfer,
      vk::PipelineStageFlagBits::eFragmentShader, subresource_range);

  FlushCommandBuffer(command_buffer, queue);
  image_layout_ = vk::ImageLayout::eShaderReadOnlyOptimal;
}

void ImageBuffer::CreateTextureImage(
    ml::Vulkan::CommandBuffer &command_buffer, vk::Queue &queue,
    const char *data, size_t size, vk::Format format,
    const ITexture::ShaderSettings &shader_settings) {
  int width, height, channels;

  stbi_uc *pixels = stbi_load_from_memory((stbi_uc const *)data, size, &width,
                                          &height, &channels, STBI_rgb_alpha);
  if (pixels == nullptr) {
    throw std::runtime_error("Could not decode image");
  }
  CreateTextureImage(command_buffer, queue, (const char *)pixels, width, height,
                     format, shader_settings);
  stbi_image_free(pixels);
}

void ImageBuffer::CreateTextureImage(
    ml::Vulkan::CommandBuffer &command_buffer, vk::Queue &queue,
    const char *data, uint32_t width, uint32_t height, vk::Format format,
    const ITexture::ShaderSettings &shader_settings) {
  bool generate_mipmaps = shader_settings.UsesMipmapping();
  uint32_t mipmap_levels = 1;
  if (generate_mipmaps) {
    mipmap_levels = GetMipmapLevels(width, height, format);
    if (mipmap_levels == 0) {
      generate_mipmaps = false;
      mipmap_levels = 1;
    }
  }

  size_t image_size = width * height * 4;

  Buffer staging_buffer(allocator_, vk::BufferUsageFlagBits::eTransferSrc,
                        VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
  staging_buffer.Alloc(image_size);
  staging_buffer.Set((const char *)data, image_size);

  CreateImage(width, height, format, vk::ImageTiling::eOptimal,
              vk::ImageUsageFlagBits::eSampled |
                  vk::ImageUsageFlagBits::eTransferDst |
                  vk::ImageUsageFlagBits::eTransferSrc,
              mipmap_levels);

  Transition(command_buffer, queue, vk::ImageLayout::eUndefined,
             vk::ImageLayout::eTransferDstOptimal);
  CopyImage(command_buffer, queue, *staging_buffer.GetBuffer(), (uint32_t)width,
            (uint32_t)height);

  if (generate_mipmaps) {
    GenerateMipmaps(command_buffer, queue, width, height, mipmap_levels);
  } else {
    Transition(command_buffer, queue, vk::ImageLayout::eTransferDstOptimal,
               vk::ImageLayout::eShaderReadOnlyOptimal);
  }

  CreateImageView(vk::ImageAspectFlagBits::eColor, mipmap_levels);
  CreateSampler(shader_settings);
}

void ImageBuffer::CreateTextureImage(ml::Vulkan::CommandBuffer &command_buffer,
                                     vk::Queue &queue, uint32_t width,
                                     uint32_t height,
                                     vk::ImageUsageFlags usage) {
  CreateImage(width, height, vk::Format::eR8G8B8A8Srgb,
              vk::ImageTiling::eOptimal, usage, 1);
  CreateImageView(vk::ImageAspectFlagBits::eColor);
  CreateSampler();
}

void ImageBuffer::CreateImage(uint32_t width, uint32_t height,
                              vk::Format format, vk::ImageTiling tiling,
                              vk::ImageUsageFlags usage, int mip_levels) {
  format_ = format;

  VkImageCreateInfo image_info = {VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO};
  image_info.imageType = VK_IMAGE_TYPE_2D;
  image_info.extent.width = width;
  image_info.extent.height = height;
  image_info.extent.depth = 1;
  image_info.mipLevels = mip_levels;
  image_info.arrayLayers = 1;
  image_info.format = static_cast<VkFormat>(format);
  image_info.tiling = static_cast<VkImageTiling>(tiling);
  image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  image_info.usage = static_cast<VkImageUsageFlags>(usage);
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  image_info.samples = VK_SAMPLE_COUNT_1_BIT;
  image_info.flags = 0;

  VmaAllocationCreateInfo image_alloc_create_info = {};
  image_alloc_create_info.usage = VMA_MEMORY_USAGE_AUTO;

  if (vmaCreateImage(allocator_, &image_info, &image_alloc_create_info,
                     (VkImage *)&image_, &allocation_, nullptr) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create image");
  }
  width_ = width;
  height_ = height;
}

void ImageBuffer::Transition(ml::Vulkan::CommandBuffer &command_buffer,
                             vk::Queue &queue, vk::ImageLayout old_layout,
                             vk::ImageLayout new_layout) {
  command_buffer.wait();
  command_buffer.reset();
  command_buffer.begin(vk::CommandBufferBeginInfo{
      vk::CommandBufferUsageFlagBits::eOneTimeSubmit});

  vk::AccessFlags src_mask{};
  vk::AccessFlags dst_mask = {};
  vk::PipelineStageFlags src_stage = {};
  vk::PipelineStageFlags dst_stage = {};

  if (old_layout == vk::ImageLayout::eUndefined &&
      new_layout == vk::ImageLayout::eTransferDstOptimal) {
    dst_mask = vk::AccessFlagBits::eTransferWrite;
    src_stage = vk::PipelineStageFlagBits::eTopOfPipe;
    dst_stage = vk::PipelineStageFlagBits::eTransfer;
  } else if (old_layout == vk::ImageLayout::eTransferDstOptimal &&
             new_layout == vk::ImageLayout::eShaderReadOnlyOptimal) {
    src_mask = vk::AccessFlagBits::eTransferWrite;
    dst_mask = vk::AccessFlagBits::eShaderRead;
    src_stage = vk::PipelineStageFlagBits::eTransfer;
    dst_stage = vk::PipelineStageFlagBits::eFragmentShader;
  } else if (old_layout == vk::ImageLayout::eUndefined &&
             new_layout == vk::ImageLayout::eDepthStencilAttachmentOptimal) {
    dst_mask = vk::AccessFlagBits::eDepthStencilAttachmentRead |
               vk::AccessFlagBits::eDepthStencilAttachmentWrite;
    src_stage = vk::PipelineStageFlagBits::eTopOfPipe;
    dst_stage = vk::PipelineStageFlagBits::eEarlyFragmentTests;
  } else if (old_layout == vk::ImageLayout::ePreinitialized &&
             new_layout == vk::ImageLayout::eShaderReadOnlyOptimal) {
    dst_mask = vk::AccessFlagBits::eShaderRead;
    src_stage = vk::PipelineStageFlagBits::eTopOfPipe;
    dst_stage = vk::PipelineStageFlagBits::eFragmentShader;
  } else if (old_layout == vk::ImageLayout::eUndefined &&
             new_layout == vk::ImageLayout::eShaderReadOnlyOptimal) {
    dst_mask = vk::AccessFlagBits::eShaderRead;
    src_stage = vk::PipelineStageFlagBits::eTopOfPipe;
    dst_stage = vk::PipelineStageFlagBits::eFragmentShader;
  } else {
    throw std::runtime_error("Unknown transition specified.");
  }

  vk::ImageAspectFlags aspect_mask;
  if (new_layout == vk::ImageLayout::eDepthStencilAttachmentOptimal) {
    aspect_mask = vk::ImageAspectFlagBits::eDepth;
    if (HasStencilComponent(format_)) {
      aspect_mask = vk::ImageAspectFlagBits::eStencil;
    }
  } else {
    aspect_mask = vk::ImageAspectFlagBits::eColor;
  }

  vk::ImageMemoryBarrier barrier{src_mask,
                                 dst_mask,
                                 old_layout,
                                 new_layout,
                                 VK_QUEUE_FAMILY_IGNORED,
                                 VK_QUEUE_FAMILY_IGNORED,
                                 image_,
                                 {
                                     aspect_mask,
                                     0,
                                     1,
                                     0,
                                     1,
                                 }};

  vk::CommandBuffer cb = command_buffer;
  cb.pipelineBarrier(src_stage, dst_stage, vk::DependencyFlagBits::eByRegion, 0,
                     nullptr, 0, nullptr, 1, &barrier);

  command_buffer.end();
  vk::SubmitInfo submitInfo{};
  submitInfo.setCommandBufferCount(1);
  submitInfo.setCommandBuffers(cb);
  auto r = queue.submit(1, &submitInfo, command_buffer);
  if (r != vk::Result::eSuccess) {
    ALOGE("Unable to submit image");
  }
  queue.waitIdle();
  image_layout_ = new_layout;
}

void ImageBuffer::CopyImage(ml::Vulkan::CommandBuffer &command_buffer,
                            vk::Queue &queue, vk::Buffer buffer, uint32_t width,
                            uint32_t height) {
  command_buffer.wait();
  command_buffer.reset();
  command_buffer.begin(vk::CommandBufferBeginInfo{
      vk::CommandBufferUsageFlagBits::eOneTimeSubmit});

  vk::BufferImageCopy region{
      0,         0,
      0,         {vk::ImageAspectFlagBits::eColor, 0, 0, 1},
      {0, 0, 0}, {width, height, 1}};

  vk::CommandBuffer cb = command_buffer;
  cb.copyBufferToImage(buffer, image_, vk::ImageLayout::eTransferDstOptimal, 1,
                       &region);
  command_buffer.end();
  vk::SubmitInfo submitInfo{};
  submitInfo.setCommandBufferCount(1);
  submitInfo.setCommandBuffers(cb);
  auto r = queue.submit(1, &submitInfo, command_buffer);
  if (r != vk::Result::eSuccess) {
    ALOGE("Unable to submit image");
  }
  queue.waitIdle();
}

void ImageBuffer::CreateImageView(vk::ImageAspectFlags aspect_flags,
                                  uint32_t levels) {
  vk::ImageViewCreateInfo view_info{
      {},      image_, vk::ImageViewType::e2D,
      format_, {},     {aspect_flags, 0, levels, 0, 1}};
  image_view_ = device_.createImageView(view_info);
}

vk::Filter ShaderSettingsToFilter(ITexture::ShaderSettings::Filter f) {
  switch (f) {
    case ITexture::ShaderSettings::NEAREST:
      return vk::Filter::eNearest;
    case ITexture::ShaderSettings::LINEAR:
      return vk::Filter::eLinear;
    case ITexture::ShaderSettings::NEAREST_MIPMAP_NEAREST:
      return vk::Filter::eNearest;
    case ITexture::ShaderSettings::LINEAR_MIPMAP_NEAREST:
      return vk::Filter::eLinear;
    case ITexture::ShaderSettings::NEAREST_MIPMAP_LINEAR:
      return vk::Filter::eNearest;
    case ITexture::ShaderSettings::LINEAR_MIPMAP_LINEAR:
      return vk::Filter::eLinear;
    default:
      return vk::Filter::eLinear;
  }
}

vk::SamplerMipmapMode ShaderSettingsToMipMapMode(
    ITexture::ShaderSettings::Filter f) {
  switch (f) {
    case ITexture::ShaderSettings::NEAREST:
      return vk::SamplerMipmapMode::eLinear;
    case ITexture::ShaderSettings::LINEAR:
      return vk::SamplerMipmapMode::eLinear;
    case ITexture::ShaderSettings::NEAREST_MIPMAP_NEAREST:
      return vk::SamplerMipmapMode::eNearest;
    case ITexture::ShaderSettings::LINEAR_MIPMAP_NEAREST:
      return vk::SamplerMipmapMode::eNearest;
    case ITexture::ShaderSettings::NEAREST_MIPMAP_LINEAR:
      return vk::SamplerMipmapMode::eLinear;
    case ITexture::ShaderSettings::LINEAR_MIPMAP_LINEAR:
      return vk::SamplerMipmapMode::eLinear;
    default:
      return vk::SamplerMipmapMode::eLinear;
  }
}

vk::SamplerAddressMode ShaderSettingsToAddressMode(
    ITexture::ShaderSettings::Wrap w) {
  switch (w) {
    case ITexture::ShaderSettings::CLAMP_TO_EDGE:
      return vk::SamplerAddressMode::eClampToEdge;
    case ITexture::ShaderSettings::MIRRORED_REPEAT:
      return vk::SamplerAddressMode::eMirroredRepeat;
    case ITexture::ShaderSettings::REPEAT:
      return vk::SamplerAddressMode::eRepeat;
    default:
      return vk::SamplerAddressMode::eRepeat;
  }
}

void ImageBuffer::CreateSampler(
    const ITexture::ShaderSettings &shader_settings) {
  vk::SamplerCreateInfo create_info{
      {},
      ShaderSettingsToFilter(shader_settings.magnification),
      ShaderSettingsToFilter(shader_settings.minification),
      ShaderSettingsToMipMapMode(shader_settings.minification),
      ShaderSettingsToAddressMode(shader_settings.u_wrap),
      ShaderSettingsToAddressMode(shader_settings.v_wrap),
      ShaderSettingsToAddressMode(shader_settings.w_wrap),
      shader_settings.lod_bias,
      false,
      1.0f};

  create_info.maxLod = VK_LOD_CLAMP_NONE;
  image_sampler_ = device_.createSampler(create_info);
}

vk::Format ImageBuffer::FindSupportedFormat(
    const std::vector<vk::Format> &candidates, vk::ImageTiling tiling,
    vk::FormatFeatureFlags features) {
  for (auto format : candidates) {
    vk::FormatProperties props;
    phys_device_.getFormatProperties(format, &props);
    if (tiling == vk::ImageTiling::eLinear &&
        (props.linearTilingFeatures & features) == features) {
      return format;
    } else if (tiling == vk::ImageTiling::eOptimal &&
               (props.optimalTilingFeatures & features) == features) {
      return format;
    }
  }
  throw std::runtime_error("FindSupportedFormat cannot support this request");
}

vk::Format ImageBuffer::FindDepthFormat() {
  return FindSupportedFormat(
      {vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint},
      vk::ImageTiling::eOptimal,
      vk::FormatFeatureFlagBits::eDepthStencilAttachment);
}

void ImageBuffer::CreateDepthImage(ml::Vulkan::CommandBuffer &command_buffer,
                                   vk::Queue &queue, uint32_t width,
                                   uint32_t height) {
  auto depth_format = FindDepthFormat();
  CreateImage(width, height, depth_format, vk::ImageTiling::eOptimal,
              vk::ImageUsageFlagBits::eDepthStencilAttachment, 1);
  CreateImageView(vk::ImageAspectFlagBits::eDepth);
  Transition(command_buffer, queue, vk::ImageLayout::eUndefined,
             vk::ImageLayout::eDepthStencilAttachmentOptimal);
}

void ImageBuffer::InsertImageMemoryBarrier(
    ml::Vulkan::CommandBuffer &command_buffer, vk::Image image,
    vk::AccessFlags src_access_mask, vk::AccessFlags dst_access_mask,
    vk::ImageLayout old_image_layout, vk::ImageLayout new_image_layout,
    vk::PipelineStageFlags src_stage_mask,
    vk::PipelineStageFlags dst_stage_mask,
    vk::ImageSubresourceRange subresource_range) {
  vk::ImageMemoryBarrier image_memory_barrier{};
  image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

  image_memory_barrier.srcAccessMask = src_access_mask;
  image_memory_barrier.dstAccessMask = dst_access_mask;
  image_memory_barrier.oldLayout = old_image_layout;
  image_memory_barrier.newLayout = new_image_layout;
  image_memory_barrier.image = image;
  image_memory_barrier.subresourceRange = subresource_range;

  ((vk::CommandBuffer &)command_buffer)
      .pipelineBarrier(src_stage_mask, dst_stage_mask,
                       vk::DependencyFlagBits::eByRegion, 0, nullptr, 0,
                       nullptr, 1, &image_memory_barrier);
}

void ImageBuffer::FlushCommandBuffer(ml::Vulkan::CommandBuffer &command_buffer,
                                     vk::Queue queue) {
  command_buffer.end();

  vk::CommandBuffer cb = command_buffer;
  vk::SubmitInfo submit_info{};
  submit_info.setCommandBufferCount(1);
  submit_info.setCommandBuffers(cb);

  // Create fence to ensure that the command buffer has finished executing

  queue.submit(submit_info, command_buffer);
}

#endif