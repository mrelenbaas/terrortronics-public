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

#include "../include/app_framework/XrMLGraphicsDeviceOpenGLES.h"

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrCore.h"

using namespace ml;

XrMLGraphicsDeviceOpenGLES::XrMLGraphicsDeviceOpenGLES(XrCore *core)
    : core_(core), swap_chain_framebuffer_(0) {
  graphics_binding_.context = EGL_NO_CONTEXT;
  graphics_binding_.display = EGL_NO_DISPLAY;
  ALOGI("XrCore using OpenGLES");
}

XrMLGraphicsDeviceOpenGLES::~XrMLGraphicsDeviceOpenGLES() {
  Destroy();
}

bool XrMLGraphicsDeviceOpenGLES::Initialize() {
  return Create();
}

std::vector<const char *> XrMLGraphicsDeviceOpenGLES::RequiredExtensions() {
  static const char *extension_name = XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME;
  return {extension_name};
}

const XrBaseInStructure *XrMLGraphicsDeviceOpenGLES::GetGraphicsBindings() {
  return reinterpret_cast<const XrBaseInStructure *>(&graphics_binding_);
}

std::pair<std::vector<XrSwapchainImageBaseHeader *>, ml::ISwapChainDataPtr>
XrMLGraphicsDeviceOpenGLES::AllocateSwapChainImageStructs(uint32_t count) {
  std::vector<XrSwapchainImageOpenGLESKHR> buffers(
      count, {.type = XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR});
  std::vector<XrSwapchainImageBaseHeader *> swap_chain_image_base;
  for (size_t i = 0; i < count; i++) {
    swap_chain_image_base.push_back(
        reinterpret_cast<XrSwapchainImageBaseHeader *>(&buffers[i]));
  }

  swap_chain_image_buffers_.push_back(std::move(buffers));
  ml::ISwapChainDataPtr p;
  return {swap_chain_image_base, p};
}

bool XrMLGraphicsDeviceOpenGLES::Create() {
  PFN_xrGetOpenGLESGraphicsRequirementsKHR
      xrGetOpenGLESGraphicsRequirementsKHR = nullptr;
  if (xrGetInstanceProcAddr(
          core_->Instance(), "xrGetOpenGLESGraphicsRequirementsKHR",
          reinterpret_cast<PFN_xrVoidFunction *>(
              &xrGetOpenGLESGraphicsRequirementsKHR)) != XR_SUCCESS) {
    ALOGE("Failed to find xrGetOpenGLESGraphicsRequirementsKHR");
    return false;
  }

  XrGraphicsRequirementsOpenGLESKHR graphicsRequirements{
      XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR};
  xrGetOpenGLESGraphicsRequirementsKHR(core_->Instance(), core_->SystemId(),
                                       &graphicsRequirements);

  EGLDisplay egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  EGLint major = 0;
  EGLint minor = 0;
  eglInitialize(egl_display, &major, &minor);
  eglBindAPI(EGL_OPENGL_ES_API);

  ALOGD("eglInitialize version %d.%d", major, minor);

  EGLint config_attribs[] = {EGL_RENDERABLE_TYPE,
                             EGL_OPENGL_ES3_BIT,
                             EGL_RED_SIZE,
                             8,
                             EGL_GREEN_SIZE,
                             8,
                             EGL_BLUE_SIZE,
                             8,
                             EGL_ALPHA_SIZE,
                             8,
                             EGL_DEPTH_SIZE,
                             24,
                             EGL_STENCIL_SIZE,
                             8,
                             EGL_SAMPLES,
                             1,
                             EGL_NONE};

  EGLint config_size = 0;
  EGLBoolean b = eglChooseConfig(egl_display, config_attribs,
                                 &graphics_binding_.config, 1, &config_size);
  if (!b) {
    ALOGE("eglChooseConfig failed");
    return false;
  }

  EGLint context_attribs[] = {EGL_CONTEXT_MAJOR_VERSION_KHR, 3,
                              EGL_CONTEXT_MINOR_VERSION_KHR, 2, EGL_NONE};
  EGLContext egl_context = eglCreateContext(
      egl_display, graphics_binding_.config, EGL_NO_CONTEXT, context_attribs);
  if (egl_context == EGL_NO_CONTEXT) {
    ALOGE("eglCreateContext failed");
    return false;
  }

  graphics_binding_.type = XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR;
  graphics_binding_.next = nullptr;
  graphics_binding_.display = egl_display;
  graphics_binding_.context = egl_context;

  eglMakeCurrent(egl_display, 0, 0, egl_context);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(
      [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
         const GLchar *message, const void *userParam) {
        ALOGE("GL Error source=%d type=% id=%d severity=%d msg=%s", source,
              type, id, severity, message);
      },
      this);

  glGenFramebuffers(1, &swap_chain_framebuffer_);
  return true;
}

void XrMLGraphicsDeviceOpenGLES::Destroy() {
  if (swap_chain_framebuffer_ != 0) {
    glDeleteFramebuffers(1, &swap_chain_framebuffer_);
    swap_chain_framebuffer_ = 0;
  }
  if (graphics_binding_.context != EGL_NO_CONTEXT) {
    eglDestroyContext(graphics_binding_.display, graphics_binding_.context);
    graphics_binding_.context = EGL_NO_CONTEXT;
  }
  if (graphics_binding_.display != EGL_NO_DISPLAY) {
    eglTerminate(graphics_binding_.display);
    graphics_binding_.display = EGL_NO_DISPLAY;
  }
}

int64_t XrMLGraphicsDeviceOpenGLES::SelectSwapChainGraphicsFormat(
    const std::vector<int64_t> &available) {
  const std::array<int64_t, 4> supported_color_swap_chain_formats{
      GL_RGBA8, GL_RGBA8_SNORM, GL_SRGB8_ALPHA8};

  auto swap_chain_format_it =
      std::find_first_of(available.begin(), available.end(),
                         supported_color_swap_chain_formats.begin(),
                         supported_color_swap_chain_formats.end());
  if (swap_chain_format_it == available.end()) {
    ALOGE("No suitable swapchain format available");
    return -1;
  }

  return *swap_chain_format_it;
}

int64_t XrMLGraphicsDeviceOpenGLES::SelectDepthSwapChainGraphicsFormat(
    const std::vector<int64_t> &available) {
  const std::array<int64_t, 2> supported_color_swap_chain_formats{
      GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT24};

  auto swap_chain_format_it =
      std::find_first_of(available.begin(), available.end(),
                         supported_color_swap_chain_formats.begin(),
                         supported_color_swap_chain_formats.end());
  if (swap_chain_format_it == available.end()) {
    ALOGE("No suitable swapchain depth format available");
    return -1;
  }

  return *swap_chain_format_it;
}

#endif