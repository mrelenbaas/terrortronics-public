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

#include "IXrMLGraphicsDevice.h"

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES

#include <map>

#include "OpenXRCommon.h"

namespace ml {
class XrCore;

class XrMLGraphicsDeviceOpenGLES : public IXrMLGraphicsDevice {
 public:
  XrMLGraphicsDeviceOpenGLES(XrCore *core);
  ~XrMLGraphicsDeviceOpenGLES();
  virtual bool Initialize() override;
  virtual std::vector<const char *> RequiredExtensions() override;
  virtual void SetupViews(
      const std::vector<XrViewConfigurationView> &config_views,
      int64_t color_format, int64_t depth_format,
      uint32_t swap_chain_image_count) override{};
  virtual std::pair<std::vector<XrSwapchainImageBaseHeader *>,
                    ISwapChainDataPtr>
  AllocateSwapChainImageStructs(uint32_t count) override;
  virtual int64_t SelectSwapChainGraphicsFormat(
      const std::vector<int64_t> &available) override;
  virtual int64_t SelectDepthSwapChainGraphicsFormat(
      const std::vector<int64_t> &available) override;

  virtual const XrBaseInStructure *GetGraphicsBindings() override;

 protected:
  bool Create();
  void Destroy();
  XrCore *core_;
  XrGraphicsBindingOpenGLESAndroidKHR graphics_binding_;
  std::vector<std::vector<XrSwapchainImageOpenGLESKHR>>
      swap_chain_image_buffers_;
  GLuint swap_chain_framebuffer_;
};

}  // namespace ml

#endif
