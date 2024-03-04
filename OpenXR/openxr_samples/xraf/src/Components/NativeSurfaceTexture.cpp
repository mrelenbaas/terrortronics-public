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

#include "../../include/app_framework/Components/NativeSurfaceTexture.h"

#ifdef XR_USE_PLATFORM_ANDROID
#include <android_native_app_glue.h>
#include <ml_native_surface.h>

#include "../../include/app_framework/ml_macros.h"

using namespace ml::Components;

NativeSurfaceTexture::NativeSurfaceTexture(uint64_t native_surface_handle)
    : native_surface_handle_(native_surface_handle),
      native_buf_handle_(ML_INVALID_HANDLE),
      encoding_type_(RAW),
      width_(1),
      height_(1),
      frame_counter_(0),
      buffer_ptr_(nullptr) {
  MLNativeSurfaceOnFrameAvailableCallback callbacks;
  MLNativeSurfaceOnFrameAvailableCallbackInit(&callbacks);

  callbacks.on_frame_available =
      [](MLHandle handle, const MLNativeSurfaceFrameAvailableInfo* info) {
        if (info && info->user_data) {
          NativeSurfaceTexture* thiz =
              reinterpret_cast<NativeSurfaceTexture*>(info->user_data);
          if (handle == thiz->native_surface_handle_) thiz->frame_counter_++;
        }
      };
  MLNativeSurfaceSetOnFrameAvailableCallback(native_surface_handle_, &callbacks,
                                             this);
}

bool NativeSurfaceTexture::Open() {
  bool is_available = frame_counter_.load() > 0;
  if (is_available) {
    frame_counter_--;
    UNWRAP_MLRESULT(MLNativeSurfaceAcquireNextAvailableFrame(
        native_surface_handle_, &native_buf_handle_));
    UNWRAP_MLRESULT(MLNativeSurfaceAcquireHardwareBufferFromNativeBuffer(
        native_surface_handle_, native_buf_handle_, &buffer_ptr_, &width_,
        &height_));

    AHardwareBuffer_acquire(buffer_ptr_);
    /**
     * Standard data that can be retrieved via AHardwareBuffer_describe():
     *   format == 35 (0x23) == AHARDWAREBUFFER_FORMAT_Y8Cb8Cr8_420
     *   flags  == 16788275:
     *               AHARDWAREBUFFER_USAGE_CPU_READ_RARELY
     *               AHARDWAREBUFFER_USAGE_CPU_READ_OFTEN
     *               AHARDWAREBUFFER_USAGE_CPU_READ_MASK
     *               AHARDWAREBUFFER_USAGE_CPU_WRITE_RARELY
     *               AHARDWAREBUFFER_USAGE_CPU_WRITE_OFTEN
     *               AHARDWAREBUFFER_USAGE_CPU_WRITE_MASK
     *               AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE
     *               AHARDWAREBUFFER_USAGE_GPU_FRAMEBUFFER
     *               AHARDWAREBUFFER_USAGE_GPU_COLOR_OUTPUT
     *               AHARDWAREBUFFER_USAGE_COMPOSER_OVERLAY
     *               AHARDWAREBUFFER_USAGE_GPU_DATA_BUFFER
     **/
  }
  return is_available;
}

bool NativeSurfaceTexture::Close() {
  return ReleaseBuffers();
}

const char* NativeSurfaceTexture::Data() {
  return reinterpret_cast<const char*>(buffer_ptr_);
}

bool NativeSurfaceTexture::ReleaseBuffers() {
  if (buffer_ptr_) {
    AHardwareBuffer_release(buffer_ptr_);
    buffer_ptr_ = nullptr;
  }
  if (MLHandleIsValid(native_buf_handle_)) {
    const MLResult res =
        MLNativeSurfaceReleaseFrame(native_surface_handle_, native_buf_handle_);
    native_buf_handle_ = ML_INVALID_HANDLE;
    if (res != MLResult_Ok) {
      UNWRAP_MLRESULT(res);
      return false;
    }
  }
  return true;
}
#endif