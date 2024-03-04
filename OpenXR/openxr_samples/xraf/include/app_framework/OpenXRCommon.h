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

#ifdef XR_USE_PLATFORM_WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif  // !WIN32_LEAN_AND_MEAN

#ifndef NOMINMAX
#define NOMINMAX
#endif  // !NOMINMAX

#include <windows.h>
#include <wrl/client.h>  // For Microsoft::WRL::ComPtr
#endif

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES

#ifndef EGL_EGLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#endif

#include <EGL/egl.h>
#include <EGL/eglext.h>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif

#include <GLES3/gl32.h>
#include <GLES3/gl3ext.h>

#endif

#ifdef XR_USE_PLATFORM_XCB
#include <GL/glx.h>
#include <X11/keysym.h>
#include <xcb/dri2.h>
#include <xcb/glx.h>
#include <xcb/randr.h>
#include <xcb/xcb.h>
#endif

#ifdef XR_USE_PLATFORM_ANDROID
#include <jni.h>
#endif

#ifndef NO_ML_CAPI
#include <ml_coordinate_frame_uid.h>
#endif

#ifdef XR_USE_GRAPHICS_API_VULKAN
#ifdef XR_USE_PLATFORM_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#ifdef XR_USE_PLATFORM_ANDROID
#ifndef VK_USE_PLATFORM_ANDROID_KHR
#define VK_USE_PLATFORM_ANDROID_KHR
#endif
#endif
#include <vk_mem_alloc.h>

#include <vulkan/vulkan.hpp>
#endif

#include <openxr/openxr.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvisibility"

#include <openxr/openxr_platform.h>

#pragma GCC diagnostic pop
