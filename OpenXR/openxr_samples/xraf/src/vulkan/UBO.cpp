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

#include "../include/app_framework/vulkan/UBO.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../include/app_framework/Logging.h"

using namespace ml::Vulkan;

UBO::UBO(vk::Device device, VmaAllocator allocator)
    : Buffer(allocator, vk::BufferUsageFlagBits::eUniformBuffer,
             VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT),
      device_(device),
      ubo_{} {
  Alloc(sizeof(ubo_));
  CreateLayout();
  AllocateDescriptorSet();
}

UBO::~UBO() {
  device_.destroyDescriptorSetLayout(layout_);
  device_.destroyDescriptorPool(descriptor_pool_);
}

void UBO::Sync() {
  Set(reinterpret_cast<const char *>(&ubo_), sizeof(ubo_));
}

void UBO::CreateLayout() {
  vk::DescriptorSetLayoutBinding ubo_layout_binding{
      0,
      vk::DescriptorType::eUniformBuffer,
      1,
      vk::ShaderStageFlagBits::eVertex | vk::ShaderStageFlagBits::eFragment,
  };

  std::array<vk::DescriptorSetLayoutBinding, 1> bindings = {ubo_layout_binding};

  vk::DescriptorSetLayoutCreateInfo descriptor_set_layout_create_info{
      {}, static_cast<uint32_t>(bindings.size()), bindings.data()};

  layout_ =
      device_.createDescriptorSetLayout(descriptor_set_layout_create_info);
}
void UBO::AllocateDescriptorSet() {
  {
    std::array<vk::DescriptorPoolSize, 1> pool_sizes{{
        {vk::DescriptorType::eUniformBuffer, 1},
    }};

    vk::DescriptorPoolCreateInfo pool_info{
        {}, 1, static_cast<uint32_t>(pool_sizes.size()), pool_sizes.data()};
    descriptor_pool_ = device_.createDescriptorPool(pool_info);

    vk::DescriptorSetAllocateInfo allocInfo{descriptor_pool_, 1, &layout_};

    auto r = device_.allocateDescriptorSets(&allocInfo, &descriptor_set_);
    if (r != vk::Result::eSuccess) {
      ALOGE("Unable to allocate descriptor sets");
    }

    vk::DescriptorBufferInfo buffer_info{*GetBuffer(), 0, VK_WHOLE_SIZE};

    std::array<vk::WriteDescriptorSet, 1> descriptor_writes{{{
        descriptor_set_,
        0,
        0,
        1,
        vk::DescriptorType::eUniformBuffer,
        {},
        &buffer_info,
    }}};

    device_.updateDescriptorSets(
        static_cast<uint32_t>(descriptor_writes.size()),
        descriptor_writes.data(), 0, nullptr);
  }
}

#endif
