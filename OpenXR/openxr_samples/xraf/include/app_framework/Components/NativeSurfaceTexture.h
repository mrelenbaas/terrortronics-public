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

#include <atomic>

#include "ITexture.h"

#ifdef XR_USE_PLATFORM_ANDROID
struct AHardwareBuffer;

namespace ml {
namespace Components {

/*! \brief NativeSurfaceTexture class.
 *
 * Stores texture data from a NativeSurface. Texture may be shared between
 * different meshes. Class is not responsible for NativeSurface creation or
 * destruction. Class will overwrite NativeSurface callback, as it is required
 * for internal use.
 */
class NativeSurfaceTexture : public ITexture {
 public:
  NativeSurfaceTexture(uint64_t native_surface_handle);

  bool Open() override;

  bool Close() override;

  const char *Data() override;

  size_t Size() override {
    return width_ * height_;
  }

  EncodingType Encoding() override {
    return encoding_type_;
  }

  TextureType Type() const override {
    return TextureType::NATIVE_SURFACE;
  }

  uint32_t Width() override {
    return width_;
  }

  uint32_t Height() override {
    return height_;
  }

  // Never used for NativeSurface handling
  const ShaderSettings &Shader() const override {
    return shader_settings_;
  }

 private:
  uint64_t native_surface_handle_, native_buf_handle_;
  EncodingType encoding_type_;
  uint32_t width_;
  uint32_t height_;
  std::atomic_int frame_counter_;
  AHardwareBuffer *buffer_ptr_;
  const ShaderSettings shader_settings_;

  bool ReleaseBuffers();
};

}  // namespace Components

}  // namespace ml
#endif