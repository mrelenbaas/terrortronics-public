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
#include "../include/app_framework/OpenXRCommon.h"

#ifdef XR_USE_PLATFORM_ANDROID
#include "../../include/app_framework/ml_macros.h"
#include "../include/app_framework/vulkan/AndroidHwBufferHelper.h"

namespace ml::Vulkan::AndroidHwBufferHelper {

bool CreateTextureImage(AHardwareBuffer* buffer, uint32_t width,
                        uint32_t height, vk::Device device, vk::Image* image,
                        vk::DeviceMemory* device_memory, vk::Format* format) {
  vk::AndroidHardwareBufferFormatPropertiesANDROID hwbFormatProps;
  vk::AndroidHardwareBufferPropertiesANDROID hwbProps({}, {}, &hwbFormatProps);

  vk::Result result =
      device.getAndroidHardwareBufferPropertiesANDROID(buffer, &hwbProps);
  if (vk::Result::eSuccess != result) {
    ALOGE("Failed to read AHardwareBuffer properties for hardware buffer %p",
          buffer);
    return false;
  }

  if (!(vk::Flags(vk::FormatFeatureFlagBits::eSampledImage) &
        vk::Flags(hwbFormatProps.formatFeatures))) {
    ALOGE("AHardwareBuffer for hardware buffer %p can't be sampled", buffer);
    return false;
  }

  if (0 == hwbProps.memoryTypeBits) {
    ALOGE(
        "AHardwareBuffer for hardware buffer %p doesn't have valid memory "
        "types",
        buffer);
    return false;
  }

  const bool useExternalFormat =
      vk::Format::eUndefined == hwbFormatProps.format;
  const vk::ExternalFormatANDROID externalFormatInfo(
      hwbFormatProps.externalFormat, nullptr);

  const vk::ExternalMemoryImageCreateInfo externalMemoryImageInfo(
      vk::ExternalMemoryHandleTypeFlagBits::eAndroidHardwareBufferANDROID,
      useExternalFormat ? &externalFormatInfo : nullptr);

  const vk::ImageUsageFlags usageFlags = {
      vk::ImageUsageFlags(vk::ImageUsageFlagBits::eSampled) |
      vk::ImageUsageFlags(vk::ImageUsageFlagBits::eTransferSrc) |
      vk::ImageUsageFlags(vk::ImageUsageFlagBits::eTransferDst)};

  const vk::ImageCreateInfo imageCreateInfo(
      {}, vk::ImageType::e2D, hwbFormatProps.format, {width, height, 1}, 1, 1,
      vk::SampleCountFlagBits::e1, vk::ImageTiling::eOptimal, usageFlags,
      vk::SharingMode::eExclusive, 0, nullptr, vk::ImageLayout::eUndefined,
      &externalMemoryImageInfo);

  result = device.createImage(&imageCreateInfo, nullptr, image);
  if (vk::Result::eSuccess != result) {
    ALOGE("Failed to create VkImage for hardware buffer %p, err: %d", buffer,
          result);
    return false;
  }

  uint32_t typeIndex = 0;
  while (0 == ((hwbProps.memoryTypeBits >> typeIndex) & 0x01)) {
    ++typeIndex;
  }

  vk::ImportAndroidHardwareBufferInfoANDROID hwbImportInfo(buffer, nullptr);
  vk::MemoryDedicatedAllocateInfo dedicatedAllocInfo(*image, {},
                                                     &hwbImportInfo);

  const vk::MemoryAllocateInfo allocInfo(hwbProps.allocationSize, typeIndex,
                                         &dedicatedAllocInfo);

  /**
   * TODO: Functionality works, but validation layers return the following error
   *here:
   *
   * Vulkan Error vkAllocateMemory: The AHardwareBuffer_Desc's format ( 35 )
   *and/or usage ( 0x1002b33 ) are not compatible with Vulkan. The Vulkan spec
   *states: If buffer is not NULL, it must be a valid Android hardware buffer
   *object with AHardwareBuffer_Desc::format and AHardwareBuffer_Desc::usage
   * compatible with Vulkan as described in Android Hardware Buffers.
   * (https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VUID-VkImportAndroidHardwareBufferInfoANDROID-buffer-01881)
   **/
  result = device.allocateMemory(&allocInfo, nullptr, device_memory);
  if (vk::Result::eSuccess != result) {
    ALOGE(
        "Failed to allocate memory for imported VkImage of hardware buffer %p, "
        "err: %d",
        buffer, result);
    return false;
  }

  vk::BindImageMemoryInfo bindImageInfo(*image, *device_memory, 0, nullptr);

  /**
   * TODO: Functionality works, but validation layers return the following error
   *here:
   *
   * Vulkan Error vkBindImageMemory2() pBindInfos[0]: memory size minus
   *memoryOffset is 0x68000 but must be at least as large as
   *VkMemoryRequirements::size value 0xa0000, returned from a call to
   * vkGetImageMemoryRequirements with image. The Vulkan spec states: The size
   *member of the VkMemoryRequirements structure returned from a call to
   *vkGetImageMemoryRequirements with image must be less than or equal to the
   *size of memory minus memoryOffset
   * (https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VUID-vkBindImageMemory-size-01049)
   **/
  result = device.bindImageMemory2(1, &bindImageInfo);
  if (vk::Result::eSuccess != result) {
    ALOGE("Failed to bind memory to VkImage for hardware buffer %p, err: %d",
          buffer, result);
    return false;
  }
  *format = hwbFormatProps.format;
  return true;
}

bool CreateSamplerYcbcrConversionCreateInfo(
    AHardwareBuffer* buffer, vk::Device device,
    vk::SamplerYcbcrConversionCreateInfo* samplerYcbcrConversionCreateInfo) {
  bool outSamplerChanged = false;
  vk::AndroidHardwareBufferFormatPropertiesANDROID hwbFormatProps;
  vk::AndroidHardwareBufferPropertiesANDROID hwbProps({}, {}, &hwbFormatProps);

  vk::Result result =
      device.getAndroidHardwareBufferPropertiesANDROID(buffer, &hwbProps);
  if (vk::Result::eSuccess != result) {
    ALOGE("Failed to read AHardwareBuffer properties for hardware buffer %p",
          buffer);
    return false;
  }

  outSamplerChanged =
      (hwbFormatProps.format != samplerYcbcrConversionCreateInfo->format) ||
      (hwbFormatProps.suggestedYcbcrModel !=
       samplerYcbcrConversionCreateInfo->ycbcrModel) ||
      (hwbFormatProps.suggestedYcbcrRange !=
       samplerYcbcrConversionCreateInfo->ycbcrRange) ||
      (std::memcmp(&hwbFormatProps.samplerYcbcrConversionComponents,
                   &samplerYcbcrConversionCreateInfo->components,
                   sizeof(VkComponentMapping)) != 0) ||
      (hwbFormatProps.suggestedXChromaOffset !=
       samplerYcbcrConversionCreateInfo->xChromaOffset) ||
      (hwbFormatProps.suggestedYChromaOffset !=
       samplerYcbcrConversionCreateInfo->yChromaOffset);

  if (outSamplerChanged) {
    samplerYcbcrConversionCreateInfo->format = hwbFormatProps.format;
    samplerYcbcrConversionCreateInfo->ycbcrModel =
        hwbFormatProps.suggestedYcbcrModel;
    samplerYcbcrConversionCreateInfo->ycbcrRange =
        hwbFormatProps.suggestedYcbcrRange;
    samplerYcbcrConversionCreateInfo->components =
        hwbFormatProps.samplerYcbcrConversionComponents;
    samplerYcbcrConversionCreateInfo->xChromaOffset =
        hwbFormatProps.suggestedXChromaOffset;
    samplerYcbcrConversionCreateInfo->yChromaOffset =
        hwbFormatProps.suggestedYChromaOffset;
    samplerYcbcrConversionCreateInfo->chromaFilter = vk::Filter::eNearest;
    samplerYcbcrConversionCreateInfo->forceExplicitReconstruction = false;
  }
  return outSamplerChanged;
}

}  // namespace ml::Vulkan::AndroidHwBufferHelper

#endif