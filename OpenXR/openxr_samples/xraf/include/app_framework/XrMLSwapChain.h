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

#include <vector>

#include "IXrMLGraphicsDevice.h"
#include "OpenXRCommon.h"

namespace ml {

class XrCore;

/*! \brief XrMLSwapChain contains all the data structures related to swap chain
 * operation. */
class XrMLSwapChain {
 public:
  XrMLSwapChain(XrCore *core, IXrMLGraphicsDevice *graphics_device);
  ~XrMLSwapChain();

  /*! \brief Allocate the graphics resources for the swapchain.
   *
   * \param view_config contains the view specific configuration
   * \param depth_chain set to true if this swapchain is a depth swapchain
   * \param color_format the color format to use for the swapchain
   * \param view_index the index of the view.
   * \return true if successful.
   * */
  bool Create(const XrViewConfigurationView &view_config, bool depth_swapchain,
              int64_t color_format, uint32_t view_index);

  /*! \brief Attempts to wait for and acquire the next available swapchain.
   *
   * The swapchain MUST be released after Acquiring.
   *
   * \return true if successful.
   */
  bool AcquireImage();

  /*! \brief Release the swapchain after it has been rendered to. */
  void ReleaseImage();

  /*! \brief Returns the width of the images in the swapchain. */
  uint32_t Width() const {
    return width_;
  }

  /*! \brief Returns the height of the images in the swapchain. */
  uint32_t Height() const {
    return height_;
  }

  /*! \brief Returns the XrSwapchain handle. */
  XrSwapchain Swapchain() const {
    return swapchain_;
  }

  /*! \brief Returns the current XrSwapchainImageBaseHeader.
   *
   * Graphics devices can cast this to their specific XrSwapChainImageXXX
   * structure.
   *
   */
  const XrSwapchainImageBaseHeader *GetSwapChainBaseHeader() const {
    if (acquired_swap_chain_image_index_ < images_.size()) {
      return images_[acquired_swap_chain_image_index_];
    } else {
      return nullptr;
    }
  }

  /*! \brief Returns the color format for the swapchain. */
  int64_t ColorFormat() const {
    return color_format_;
  }

  /*! \brief Returns the number of images in the swapchain. */
  uint32_t ImageCount() const {
    return images_.size();
  }

  /*! \brief Returns the index of the acquired image from the swapchain. */
  uint32_t AcquiredSwapChainIndex() const {
    return acquired_swap_chain_image_index_;
  }

 private:
  XrCore *core_;
  IXrMLGraphicsDevice *graphics_device_;
  XrSwapchain swapchain_;
  std::vector<XrSwapchainImageBaseHeader *> images_;
  uint32_t width_;
  uint32_t height_;
  int64_t color_format_;
  ISwapChainDataPtr graphics_device_swap_chain_data_;
  uint32_t acquired_swap_chain_image_index_;

  void Destroy();
};

}  // namespace ml
