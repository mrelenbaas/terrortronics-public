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

#include <openxr/openxr.h>

#include <memory>
#include <utility>
#include <vector>

namespace ml {

class IGuiBackend;

class XrCore;
class XrMLSwapChain;

class ISwapChainData {
 public:
  virtual ~ISwapChainData() {
  }
};
using ISwapChainDataPtr = std::shared_ptr<ISwapChainData>;

class IXrMLGraphicsDevice {
 public:
  enum DeviceType { Unknown, Vulkan, OpenGLES, OpenGL };

  static DeviceType StringToDeviceType(const char *device_type);
  static const char *DeviceTypeToString(DeviceType device_type);

  // *****************************
  // IXrMLGraphicsDevice Interface
  // *****************************
  virtual ~IXrMLGraphicsDevice() {
  }

  // called prior to initialization of the OpenXR instance.
  virtual void PreInstanceInitialize(
      const std::vector<XrExtensionProperties> &extensions){};
  // allocate the graphics resources.
  virtual bool Initialize() = 0;
  // returns a vector of names of OpenXR extensions that this graphics device
  // requires.
  virtual std::vector<const char *> RequiredExtensions() = 0;

  // this is called before the applications begins teardown
  // of the graphics stack. It allows the graphics
  // device to finish anything that needs to.
  virtual void Finish(){};

  // Allow the graphics device to allocate resources needed.
  virtual void SetupViews(
      const std::vector<XrViewConfigurationView> &config_views,
      int64_t color_format, int64_t depth_format,
      uint32_t swap_chain_image_count) = 0;
  // allocates memory for the Swap Chain Image Structs.
  // these are valid until the object is destroyed.
  virtual std::pair<std::vector<XrSwapchainImageBaseHeader *>,
                    ISwapChainDataPtr>
  AllocateSwapChainImageStructs(uint32_t count) = 0;
  // returns the graphics bindings required to create an XrSession.
  virtual const XrBaseInStructure *GetGraphicsBindings() = 0;
  // Pick the graphics format to use for the color buffer.
  virtual int64_t SelectSwapChainGraphicsFormat(
      const std::vector<int64_t> &available) = 0;
  // Pick the graphics format to use for the depth buffer.
  virtual int64_t SelectDepthSwapChainGraphicsFormat(
      const std::vector<int64_t> &available) = 0;
  // Called before the first render call.
  virtual bool StartOfRenderLoop() {
    return true;
  };
  // called before each render
  virtual void RenderFrame(){};
  // render the view!
  virtual void RenderView(XrCompositionLayerProjectionView &projection_view,
                          const XrMLSwapChain *color_swap_chain,
                          const XrMLSwapChain *depth_swap_chain,
                          uint32_t view) = 0;
  // return a pointer to the gui object, there can only be one.
  virtual IGuiBackend *GetGui() = 0;

  virtual void UpdateViewMatrix(const std::vector<XrView> &views){};

  // waits for the current render pass to finish completely. This is
  // needed if the scene graph gets updated but rendering is still in flight.
  virtual void WaitForFrameRenderFinished() {
  }
};

}  // namespace ml
