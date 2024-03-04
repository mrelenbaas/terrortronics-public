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

#include "../include/app_framework/IXrMLGraphicsDevice.h"

#include "../include/app_framework/Logging.h"
#include "../include/app_framework/XrMLGraphicsDeviceOpenGLES.h"
#include "../include/app_framework/XrMLGraphicsDeviceVulkan.h"

static const char *Unknown_String = "Unknown";
static const char *OpenGLES_String = "OpenGLES";
static const char *OpenGL_String = "OpenGL";
static const char *Vulkan_String = "Vulkan";

using namespace ml;

IXrMLGraphicsDevice::DeviceType IXrMLGraphicsDevice::StringToDeviceType(
    const char *device_type) {
  if (strcmp(device_type, OpenGLES_String) == 0) {
    return OpenGLES;
  }
  if (strcmp(device_type, OpenGL_String) == 0) {
    return OpenGL;
  }
  if (strcmp(device_type, Vulkan_String) == 0) {
    return Vulkan;
  }
  return Unknown;
}

const char *IXrMLGraphicsDevice::DeviceTypeToString(DeviceType device_type) {
  switch (device_type) {
    case IXrMLGraphicsDevice::OpenGLES:
      return OpenGLES_String;
    case IXrMLGraphicsDevice::OpenGL:
      return OpenGL_String;
    case IXrMLGraphicsDevice::Vulkan:
      return Vulkan_String;
    default:
      return Unknown_String;
  };
}
