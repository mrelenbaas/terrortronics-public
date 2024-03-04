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

#ifdef XR_USE_PLATFORM_ANDROID
#include <jni.h>
#endif

#include <app_framework/Logging.h>
#include <app_framework/Utils/AndroidHelper.h>
#include <app_framework/Utils/SystemHelper.h>
#include <app_framework/XrAndroidCore.h>
#include <app_framework/XrAppSimCore.h>
#include <app_framework/XrHostCore.h>
#include <app_framework/XrMLGraphicsDeviceOpenGLES.h>
#include <app_framework/XrMLGraphicsDeviceVulkan.h>

#include <chrono>
#include <thread>

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

using namespace ml;

// Create very simple graphics rendering implementations
// for Vulkan and OpenGL

class BackgroundClearColor {
 public:
  virtual void SetClearColors(std::array<float, 4> &color_left,
                              std::array<float, 4> &color_right) {
    clear_color_left_ = color_left;
    clear_color_right_ = color_right;
  }

 protected:
  std::array<float, 4> clear_color_left_;
  std::array<float, 4> clear_color_right_;
};
#ifdef XR_USE_GRAPHICS_API_VULKAN
class BasicVulkanGraphicsDevice : public XrMLGraphicsDeviceVulkan,
                                  public BackgroundClearColor {
 public:
  BasicVulkanGraphicsDevice(XrCore *core) : XrMLGraphicsDeviceVulkan(core) {
  }
  IGuiBackend *GetGui() override {
    return nullptr;
  }
  virtual void RenderView(XrCompositionLayerProjectionView &projection_view,
                          const XrMLSwapChain *color_swap_chain,
                          const XrMLSwapChain *depth_swap_chain,
                          uint32_t view) override {
    assert(color_swap_chain != nullptr);
    assert(depth_swap_chain != nullptr);

    std::array<vk::ClearValue, 2> clearValues;

    if (view == 0) {
      clearValues[0].color.float32[0] = clear_color_left_[0];
      clearValues[0].color.float32[1] = clear_color_left_[1];
      clearValues[0].color.float32[2] = clear_color_left_[2];
      clearValues[0].color.float32[3] = clear_color_left_[3];
    } else {
      clearValues[0].color.float32[0] = clear_color_right_[0];
      clearValues[0].color.float32[1] = clear_color_right_[1];
      clearValues[0].color.float32[2] = clear_color_right_[2];
      clearValues[0].color.float32[3] = clear_color_right_[3];
    }
    vk::RenderPassBeginInfo rps({}, {}, {}, clearValues.size(),
                                &clearValues[0]);

    vk::CommandBuffer cb = command_buffers_[view];

    command_buffers_[view].wait();
    command_buffers_[view].reset();
    command_buffers_[view].begin();

    BindRenderPass(view, color_swap_chain, depth_swap_chain, rps);

    cb.beginRenderPass(rps, vk::SubpassContents::eInline);

    cb.endRenderPass();
    cb.end();
    vk::SubmitInfo submit_info(0, nullptr, nullptr, 1, &cb);
    queue_.submit(submit_info, command_buffers_[view]);
  }
};
#endif

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES
class BasicOpenGLESGraphicsDevice : public XrMLGraphicsDeviceOpenGLES,
                                    public BackgroundClearColor {
 public:
  BasicOpenGLESGraphicsDevice(XrCore *core) : XrMLGraphicsDeviceOpenGLES(core) {
  }
  IGuiBackend *GetGui() override {
    return nullptr;
  }
  virtual void RenderView(XrCompositionLayerProjectionView &projection_view,
                          const XrMLSwapChain *color_swap_chain,
                          const XrMLSwapChain *depth_swap_chain,
                          uint32_t view) override {
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    const XrSwapchainImageOpenGLESKHR *csi =
        reinterpret_cast<const XrSwapchainImageOpenGLESKHR *>(
            color_swap_chain->GetSwapChainBaseHeader());
    const XrSwapchainImageOpenGLESKHR *dsi =
        reinterpret_cast<const XrSwapchainImageOpenGLESKHR *>(
            depth_swap_chain->GetSwapChainBaseHeader());

    glViewport(
        static_cast<GLint>(projection_view.subImage.imageRect.offset.x),
        static_cast<GLint>(projection_view.subImage.imageRect.offset.y),
        static_cast<GLsizei>(projection_view.subImage.imageRect.extent.width),
        static_cast<GLsizei>(projection_view.subImage.imageRect.extent.height));
    glBindFramebuffer(GL_FRAMEBUFFER, swap_chain_framebuffer_);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           csi->image, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                           dsi->image, 0);

    if (view == 0) {
      glClearColor(clear_color_left_[0], clear_color_left_[1],
                   clear_color_left_[2], clear_color_left_[3]);
    } else {
      glClearColor(clear_color_right_[0], clear_color_right_[1],
                   clear_color_right_[2], clear_color_right_[3]);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
};
#endif
/* *********************************************************************************
 */
/* Android Native Activity Handling */
/* *********************************************************************************
 */

bool GetGraphics(IXrMLGraphicsDevice::DeviceType device_type, XrCore *core,
                 std::unique_ptr<IXrMLGraphicsDevice> &device,
                 BackgroundClearColor **background_clear_color) {
  switch (device_type) {
    case IXrMLGraphicsDevice::Vulkan:
#ifdef XR_USE_GRAPHICS_API_VULKAN
      ALOGI("Using Vulkan graphics backend");
      device = std::make_unique<BasicVulkanGraphicsDevice>(core);
      *background_clear_color =
          dynamic_cast<BackgroundClearColor *>(device.get());
      return true;
#else
      ALOGE("Vulkan graphics backend unavailable!");
      return false;
#endif

    case IXrMLGraphicsDevice::OpenGLES:
#ifdef XR_USE_GRAPHICS_API_OPENGL_ES
      ALOGI("Using OpenGLES graphics backend");
      device = std::make_unique<BasicOpenGLESGraphicsDevice>(core);
      *background_clear_color =
          dynamic_cast<BackgroundClearColor *>(device.get());
      return true;
#else
      ALOGE("OpenGLES graphics backend unavailable!");
      return false;
#endif
    default:
      return false;
  }
}

static IXrMLGraphicsDevice::DeviceType StringToGraphicsDevice(
    const char *graphics_device) {
  if (strcasecmp(graphics_device, "vulkan") == 0) {
    return IXrMLGraphicsDevice::Vulkan;
  } else if (strcasecmp(graphics_device, "opengles") == 0) {
    return IXrMLGraphicsDevice::OpenGLES;
  } else {
    ALOGW("Unknown graphics type requested %s, defaulting to Vulkan",
          graphics_device);
    return IXrMLGraphicsDevice::Vulkan;
  }
}

static IXrMLGraphicsDevice::DeviceType GetGraphicsDeviceType(
    struct android_app *state) {
  ml::SystemHelper system_helper(state);
  auto intents = system_helper.GetIntentExtras();
  auto graphics_itr = intents.find("graphics");
  if (graphics_itr != intents.end()) {
    return StringToGraphicsDevice(graphics_itr->second.c_str());
  }
  return IXrMLGraphicsDevice::Vulkan;
}

void android_main(struct android_app *state) {
  IXrMLGraphicsDevice::DeviceType graphics_device_type =
      GetGraphicsDeviceType(state);

  struct AppStatus {
    android_app *state;
    int frame_cntr;
    BackgroundClearColor *background_clear_color;
    std::chrono::time_point<std::chrono::steady_clock> start_;
    std::unique_ptr<XrCore> xr_core;
  };
  AppStatus status{state, 0, nullptr};

  XrCoreCallbacks callbacks{
      [&status]() { status.start_ = std::chrono::steady_clock::now(); },
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      [&status](float delta) {
        auto runtime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                              std::chrono::steady_clock::now() - status.start_)
                              .count();
        float factor = labs(runtime_ms % 2000 - 1000) / 1000.0;
        std::array<float, 4> left = {1.0f - factor, 0.0f, 0.0f, 0.0f};
        std::array<float, 4> right = {0.0f, 0.0f, factor, 0.0f};

        status.background_clear_color->SetClearColors(left, right);

        status.frame_cntr++;
        if (status.frame_cntr == 300) {
          status.xr_core->FinishActivity();
        }
      },
      nullptr};

  try {
#ifdef XR_USE_PLATFORM_ANDROID
    status.xr_core = std::make_unique<XrAndroidCore>(ALOG_TAG, state);
#elif defined XRAF_USE_HOST_CORE
    status.xr_core = std::make_unique<XrHostCore>(ALOG_TAG);
#else
    status.xr_core = std::make_unique<XrAppSimCore>(ALOG_TAG, state);
#endif

    std::unique_ptr<IXrMLGraphicsDevice> graphics_device;
    if (!GetGraphics(graphics_device_type, status.xr_core.get(),
                     graphics_device, &status.background_clear_color)) {
      ALOGE("Unable to create graphics device");
      return;
    }

    // takes ownership of graphics device.
    status.xr_core->Initialize(graphics_device, callbacks, {}, {});

  } catch (std::runtime_error &e) {
    ALOGE("Failed to create XrCore: %s", e.what());
    return;
  }

  status.xr_core->RenderLoop();

  // force cleanup here
  status.xr_core.reset();

  ALOGV("android_main exit.");
}
