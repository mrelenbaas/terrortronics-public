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

#ifdef XR_USE_PLATFORM_ANDROID
namespace ml {
namespace Vulkan {

/*! \brief ImmutableYcbcrSampler class.
 *
 * Class for creating a Sampler that uses SamplerYcbcrConversion.
 * Implemented as singleton so it's easier to use as pImmutableSampler in
 * DescriptorSetLayout (as it requires the exact same SamplerYcbcrConversionInfo
 * to be provided in ImageView, when updating a DescriptorSet that uses said
 * layout).
 *
 * Hardcoded with values based on NativeSurface usage.
 */
class ImmutableYcbcrSampler {
 public:
  ImmutableYcbcrSampler(ImmutableYcbcrSampler const&) = delete;
  void operator=(ImmutableYcbcrSampler const&) = delete;

  static ImmutableYcbcrSampler* GetInstance();

  void Initialize(vk::Device device);
  void Destroy(vk::Device device);

  const vk::Sampler& GetSampler() const;
  const vk::SamplerYcbcrConversionInfo& GetSamplerConversionInfo() const;

 private:
  vk::SamplerYcbcrConversion sampler_ycbcr_conversion_;
  vk::SamplerYcbcrConversionCreateInfo sampler_ycbcr_conversion_create_info_;
  vk::SamplerYcbcrConversionInfo sampler_ycbcr_conversion_info_;
  vk::Sampler sampler_;

  ImmutableYcbcrSampler(){};
};

}  // namespace Vulkan
}  // namespace ml
#endif