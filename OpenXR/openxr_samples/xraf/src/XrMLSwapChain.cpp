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

#include "../include/app_framework/XrMLSwapChain.h"

#include <cassert>

#include "../include/app_framework/IXrMLGraphicsDevice.h"
#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"

#ifdef XRAF_USE_ANDROID_CORE
#include "../include/app_framework/XrAndroidCore.h"
#endif

#define INVALID_SWAP_CHAIN_INDEX 0xffffffff

using namespace ml;

XrMLSwapChain::XrMLSwapChain(ml::XrCore *core,
                             IXrMLGraphicsDevice *graphics_device)
    : core_(core),
      graphics_device_(graphics_device),
      swapchain_(XR_NULL_HANDLE),
      width_(0),
      height_(0),
      color_format_(0),
      acquired_swap_chain_image_index_(INVALID_SWAP_CHAIN_INDEX) {
  assert(core_ != nullptr);
  assert(graphics_device_ != nullptr);
}

XrMLSwapChain::~XrMLSwapChain() {
  Destroy();
}

bool XrMLSwapChain::Create(const XrViewConfigurationView &view_config,
                           bool depth_swapchain, int64_t color_format,
                           uint32_t view_index) {
  width_ = view_config.recommendedImageRectWidth;
  height_ = view_config.recommendedImageRectHeight;
  color_format_ = color_format;

  uint32_t create_flags =
      XR_SWAPCHAIN_USAGE_SAMPLED_BIT | XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;

  if (depth_swapchain) {
    create_flags = XR_SWAPCHAIN_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |
                   XR_SWAPCHAIN_USAGE_SAMPLED_BIT;
  }

  XrSwapchainCreateInfo swap_chain_create_info{
      .type = XR_TYPE_SWAPCHAIN_CREATE_INFO,
      .next = nullptr,
      .createFlags = 0,
      .usageFlags = create_flags,
      .format = color_format_,
      .sampleCount = 1,
      .width = width_,
      .height = height_,
      .faceCount = 1,
      .arraySize = 1,
      .mipCount = 1,
  };

  if (xrCreateSwapchain(core_->Session(), &swap_chain_create_info,
                        &swapchain_) != XR_SUCCESS) {
    ALOGE("xrCreateSwapchain failed.");
    return false;
  }

  uint32_t image_count;
  if (xrEnumerateSwapchainImages(swapchain_, 0, &image_count, nullptr) !=
      XR_SUCCESS) {
    return false;
  }

  if (image_count == 0) {
    return false;
  }

  std::tie(images_, graphics_device_swap_chain_data_) =
      graphics_device_->AllocateSwapChainImageStructs(image_count);

  if (xrEnumerateSwapchainImages(swapchain_, image_count, &image_count,
                                 images_[0]) != XR_SUCCESS) {
    ALOGE("Failed to xrEnumerateSwapchainImages");
    return false;
  }

  return true;
}

void XrMLSwapChain::Destroy() {
  if (swapchain_ != XR_NULL_HANDLE) {
    xrDestroySwapchain(swapchain_);
    swapchain_ = XR_NULL_HANDLE;
  }
  graphics_device_swap_chain_data_.reset();
}

bool XrMLSwapChain::AcquireImage() {
  if (acquired_swap_chain_image_index_ != INVALID_SWAP_CHAIN_INDEX) {
    ALOGE("SwapChain Image already acquired!");
    return false;
  }

  XrSwapchainImageAcquireInfo acquire_info{
      XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO};

  if (xrAcquireSwapchainImage(swapchain_, &acquire_info,
                              &acquired_swap_chain_image_index_) !=
      XR_SUCCESS) {
    acquired_swap_chain_image_index_ = INVALID_SWAP_CHAIN_INDEX;
    ALOGE("xrAcquireSwapchainImage failed.");
    return false;
  }

  XrSwapchainImageWaitInfo waitInfo{XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO};
  XrDuration const micro_seconds = 1000000;
  waitInfo.timeout = 100 * micro_seconds;
  while (xrWaitSwapchainImage(swapchain_, &waitInfo) != XR_SUCCESS) {
// If xrWaitSwapchainImage times out it is likely
// the user was switching back and forward between
// home and the app at 'just the right time'.
//
// The OS is unable to release the wait if we are not pumping the
// Android state machine.
// GRAPH-3559
#ifdef XRAF_USE_ANDROID_CORE
    auto android = dynamic_cast<XrAndroidCore *>(core_);
    if (android) {
      ALOGE("xrWaitSwapchainImage timed-out, processing Android Events...");
      while (true) {
        int timeout_ms =
            core_->SessionState() < XR_SESSION_STATE_VISIBLE ? -1 : 0;
        if (!android->ProcessSingle(timeout_ms)) {
          break;
        }
      }
    }
#endif
  }

  return true;
}

void XrMLSwapChain::ReleaseImage() {
  if (acquired_swap_chain_image_index_ != INVALID_SWAP_CHAIN_INDEX) {
    XrSwapchainImageReleaseInfo release_info{
        XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO};
    if (xrReleaseSwapchainImage(swapchain_, &release_info) != XR_SUCCESS) {
      ALOGE("xrReleaseSwapchainImage failed.");
    }
    acquired_swap_chain_image_index_ = INVALID_SWAP_CHAIN_INDEX;
  }
}
