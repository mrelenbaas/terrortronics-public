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

#include "../OpenXRCommon.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include <memory>
#include <vector>

#include "../Components/Material.h"

using namespace ml::Components;

namespace ml {
namespace Vulkan {

class ImageBuffer;
using ImageBufferPtr = std::shared_ptr<ImageBuffer>;

class TextureDescriptorPool {
 public:
  enum PipelineLayoutType { UNLIT, NATIVE_BUFFER, PBR };

  TextureDescriptorPool(vk::Device device, PipelineLayoutType pipeline_type,
                        uint32_t max_image_count = 1000)
      : device_(device),
        pipeline_type_(pipeline_type),
        layout_(CreateLayout()) {
    AllocatePool(max_image_count);
  }

  ~TextureDescriptorPool();

  TextureDescriptorPool(const TextureDescriptorPool &) = delete;
  TextureDescriptorPool &operator=(const TextureDescriptorPool &) = delete;
  TextureDescriptorPool(TextureDescriptorPool &&source) {
    device_ = std::move(source.device_);
    pipeline_type_ = source.pipeline_type_;
    layout_ = std::move(source.layout_);
    pool_ = std::move(source.pool_);
  }

  TextureDescriptorPool &operator=(TextureDescriptorPool &&source) {
    device_ = std::move(source.device_);
    pipeline_type_ = source.pipeline_type_;
    layout_ = std::move(source.layout_);
    pool_ = std::move(source.pool_);
    return *this;
  }

  inline vk::DescriptorSetLayout &DescriptorSetLayout() {
    return layout_;
  }

  inline PipelineLayoutType Type() const {
    return pipeline_type_;
  }

  inline vk::DescriptorPool Pool() {
    return pool_;
  }

 protected:
  void AllocatePool(uint32_t max_image_count);

  vk::Device device_;
  PipelineLayoutType pipeline_type_;
  vk::DescriptorSetLayout layout_;
  vk::DescriptorPool pool_;
  vk::SamplerYcbcrConversion samplerYcbcrConversion_;
  vk::Sampler immutable_sampler_;

  vk::DescriptorSetLayout CreateLayout();
};
}  // namespace Vulkan
}  // namespace ml

#endif
