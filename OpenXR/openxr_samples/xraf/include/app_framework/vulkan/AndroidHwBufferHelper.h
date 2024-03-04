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
struct AHardwareBuffer;

namespace ml {
namespace Vulkan {
namespace AndroidHwBufferHelper {

/*! \brief Creates VkImage from provided AHardwareBuffer pointer.
 *
 * User is required to destroy created VkImage and free allocated
 * VkDeviceMemory.
 *
 * @param buffer pointer to Android hardware buffer
 * @param width image width
 * @param height image height
 * @param device VkDevice to perform operations with
 * @param image pointer to struct that will be filled with new VkImage
 * @param device_memory pointer to struct that will be filled with allocated
 * memory
 * @param format pointer to struct that will be filled with VkImage's format
 *
 * @return true if successful.
 */
bool CreateTextureImage(AHardwareBuffer* buffer, uint32_t width,
                        uint32_t height, vk::Device device, vk::Image* image,
                        vk::DeviceMemory* device_memory, vk::Format* format);

/*! \brief Updates VkSamplerYcbcrConversionCreateInfo if needed, based on the
 * provided AHardwareBuffer pointer.
 *
 * @param buffer pointer to Android hardware buffer
 * @param device VkDevice to use for buffer info querying
 * @param samplerYcbcrConversionCreateInfo pointer to struct that will be filled
 * with new VkSamplerYcbcrConversionCreateInfo
 *
 * @return true if samplerYcbcrConversionCreateInfo was changed.
 */
bool CreateSamplerYcbcrConversionCreateInfo(
    AHardwareBuffer* buffer, vk::Device device,
    vk::SamplerYcbcrConversionCreateInfo* samplerYcbcrConversionCreateInfo);

}  // namespace AndroidHwBufferHelper
}  // namespace Vulkan
}  // namespace ml

#endif