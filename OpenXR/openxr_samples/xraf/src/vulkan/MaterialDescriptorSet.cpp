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

#include "../include/app_framework/vulkan/MaterialDescriptorSet.h"

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/vulkan/ImageBuffer.h"
#include "../include/app_framework/vulkan/NativeImageBuffer.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

using namespace ml::Vulkan;

// TODO honor material.alphaMode
// TODO honot material.doubleSided

// start of material setup.
void MaterialDescriptorSet::StartSetup() {
  images_.clear();
}

void MaterialDescriptorSet::AddImage(Material::TextureType texture_type,
                                     ImageBufferPtr &image) {
  images_[texture_type] = image;
}
// once finished, this creates the descriptor set.
void MaterialDescriptorSet::FinishSetup(vk::Device device) {
  vk::DescriptorSetAllocateInfo allocInfo{
      descriptor_pool_->Pool(),
      1,
      &descriptor_pool_->DescriptorSetLayout(),
  };

  auto r = device.allocateDescriptorSets(&allocInfo, &descriptor_set_);
  if (r != vk::Result::eSuccess) {
    ALOGE("Unable to allocate descriptor sets");
  }

  UpdateDescriptorSet(device);
}

void MaterialDescriptorSet::UpdateDescriptorSet(vk::Device device) {
  std::vector<vk::WriteDescriptorSet> descriptor_writes;

  uint32_t texture_count = 0;

  switch (descriptor_pool_->Type()) {
    case TextureDescriptorPool::UNLIT:
    case TextureDescriptorPool::NATIVE_BUFFER:
      texture_count = 1;
      break;
    case TextureDescriptorPool::PBR:
      texture_count = Material::TEXTURE_TYPE_COUNT;
      break;
  }

  std::vector<vk::DescriptorImageInfo> image_descriptors;
  image_descriptors.resize(texture_count);

  for (uint32_t i = 0; i < texture_count; i++) {
    const auto texture_type = (ml::Components::Material::TextureType)i;
    auto image = images_[texture_type];
    if (image == nullptr || !image->Image()) {
      const auto it = default_images_.find(texture_type);
      if (it == default_images_.end()) {
        ALOGE("No default image for texture type %d", i);
        return;
      } else {
        image = it->second;
      }
    } else {
      has_image_[texture_type] = true;
    }

    vk::DescriptorImageInfo info = image->DescriptorImageInfo();
    image_descriptors[i] = info;

    vk::WriteDescriptorSet wds(descriptor_set_,
                               i,  // binding
                               0,  // array
                               1,  // count,
                               vk::DescriptorType::eCombinedImageSampler,
                               &image_descriptors[i]);
    descriptor_writes.push_back(wds);
  }
  device.updateDescriptorSets(static_cast<uint32_t>(descriptor_writes.size()),
                              descriptor_writes.data(), 0, nullptr);
}

void MaterialDescriptorSet::UpdateIfNative(
    vk::Device device, ml::Vulkan::CommandBuffer &command_buffer,
    vk::Queue &queue) {
#ifdef XR_USE_PLATFORM_ANDROID
  if (descriptor_pool_->Type() != TextureDescriptorPool::NATIVE_BUFFER) return;

  const auto texture_type = ml::Components::Material::COLOR;
  auto image = images_[texture_type];
  if (image && image->PreRenderUpdate(command_buffer, queue)) {
    has_image_[texture_type] = true;
    UpdateDescriptorSet(device);
  }
#endif
}

#endif
