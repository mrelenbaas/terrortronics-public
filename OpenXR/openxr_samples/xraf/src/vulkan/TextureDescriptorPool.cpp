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

#include "../../include/app_framework/vulkan/TextureDescriptorPool.h"

#include "../../include/app_framework/vulkan/ImageBuffer.h"
#include "../include/app_framework/vulkan/ImmutableYcbcrSampler.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../include/app_framework/Logging.h"

using namespace ml::Vulkan;

TextureDescriptorPool::~TextureDescriptorPool() {
  if (device_ && pool_) {
    device_.destroyDescriptorPool(pool_);
  }
  if (layout_) {
    device_.destroyDescriptorSetLayout(layout_);
  }
}

void TextureDescriptorPool::AllocatePool(uint32_t max_image_count) {
  std::array<vk::DescriptorPoolSize, 1> pool_sizes{
      {{vk::DescriptorType::eCombinedImageSampler, max_image_count}}};

  vk::DescriptorPoolCreateInfo pool_info{
      {},
      static_cast<uint32_t>(max_image_count),
      static_cast<uint32_t>(pool_sizes.size()),
      pool_sizes.data()};

  pool_ = device_.createDescriptorPool(pool_info);
}

vk::DescriptorSetLayout TextureDescriptorPool::CreateLayout() {
  std::vector<vk::DescriptorSetLayoutBinding> bindings;
  switch (pipeline_type_) {
    case PBR: {
      bindings.reserve(Material::TEXTURE_TYPE_COUNT);

      for (uint32_t i = 0; i < Material::TEXTURE_TYPE_COUNT; i++) {
        bindings.emplace_back(i, vk::DescriptorType::eCombinedImageSampler, 1,
                              vk::ShaderStageFlagBits::eFragment, nullptr);
      }
      break;
    }

    case NATIVE_BUFFER: {
#ifdef XR_USE_PLATFORM_ANDROID
      bindings.emplace_back(
          0, vk::DescriptorType::eCombinedImageSampler, 1,
          vk::ShaderStageFlagBits::eFragment,
          &ImmutableYcbcrSampler::GetInstance()->GetSampler());
      break;
#else
      [[fallthrough]];
#endif
    }

    case UNLIT: {
      bindings.emplace_back(0, vk::DescriptorType::eCombinedImageSampler, 1,
                            vk::ShaderStageFlagBits::eFragment, nullptr);
      break;
    }
  }
  vk::DescriptorSetLayoutCreateInfo descriptor_set_layout_create_info{
      {}, static_cast<uint32_t>(bindings.size()), bindings.data()};
  return device_.createDescriptorSetLayout(descriptor_set_layout_create_info);
}

#endif