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

#include "../include/app_framework/Logging.h"

#ifdef XR_USE_PLATFORM_ANDROID

#include "../include/app_framework/vulkan/ImmutableYcbcrSampler.h"

using namespace ml::Vulkan;

void ImmutableYcbcrSampler::Initialize(vk::Device device) {
  sampler_ycbcr_conversion_create_info_ = vk::SamplerYcbcrConversionCreateInfo(
      vk::Format::eG8B8R82Plane420Unorm,
      vk::SamplerYcbcrModelConversion::eYcbcr601,
      vk::SamplerYcbcrRange::eItuFull, {}, vk::ChromaLocation::eMidpoint,
      vk::ChromaLocation::eMidpoint, vk::Filter::eNearest, {}, nullptr);
  const vk::Result result = device.createSamplerYcbcrConversion(
      &sampler_ycbcr_conversion_create_info_, nullptr,
      &sampler_ycbcr_conversion_);
  if (result != vk::Result::eSuccess) {
    ALOGE("vkCreateSamplerYcbcrConversion failed!");
  }
  sampler_ycbcr_conversion_info_.conversion = sampler_ycbcr_conversion_;

  const vk::SamplerCreateInfo create_info(
      {}, vk::Filter::eNearest, vk::Filter::eNearest,
      vk::SamplerMipmapMode::eNearest, vk::SamplerAddressMode::eClampToEdge,
      vk::SamplerAddressMode::eClampToEdge,
      vk::SamplerAddressMode::eClampToEdge, 0.f, false, 1.0f, false,
      vk::CompareOp::eAlways, 0.f, 0.f, vk::BorderColor::eIntTransparentBlack,
      false, &sampler_ycbcr_conversion_info_);
  sampler_ = device.createSampler(create_info);
}

ImmutableYcbcrSampler* ImmutableYcbcrSampler::GetInstance() {
  static ImmutableYcbcrSampler instance;
  return &instance;
}

void ImmutableYcbcrSampler::Destroy(vk::Device device) {
  if (sampler_) {
    device.destroySampler(sampler_, nullptr);
  }
  if (sampler_ycbcr_conversion_) {
    device.destroySamplerYcbcrConversion(sampler_ycbcr_conversion_, nullptr);
  }
}

const vk::Sampler& ImmutableYcbcrSampler::GetSampler() const {
  return sampler_;
}

const vk::SamplerYcbcrConversionInfo&
ImmutableYcbcrSampler::GetSamplerConversionInfo() const {
  return sampler_ycbcr_conversion_info_;
}

#endif