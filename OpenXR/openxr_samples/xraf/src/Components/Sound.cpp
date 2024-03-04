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

#include "../../include/app_framework/Components/Sound.h"

#ifndef NO_ML_CAPI
#include <ml_audio.h>
#endif
#include <cstring>

#include "../../include/app_framework/ml_macros.h"

#define UNWRAP_MLAudioResult(result) \
  MLRESULT_EXPECT((result), MLResult_Ok, MLAudioGetResultString, ALOG_ERROR)

using namespace ml::Components;

Sound::Sound(const std::vector<uint8_t> &raw_buffer, int channels,
             int sample_rate, int bits_per_sample)
    :
#ifndef NO_ML_CAPI
      audio_handle_{static_cast<MLHandle>(ML_INVALID_HANDLE)},
#endif
      raw_buffer_(raw_buffer),
      channels_(channels),
      sample_rate_(sample_rate),
      bits_per_sample_(bits_per_sample),
      looping_(false) {
  CreateAudio();
}

Sound::~Sound() {
  DestroyAudio();
}

void Sound::Play() {
#ifndef NO_ML_CAPI
  if (audio_handle_ != ML_INVALID_HANDLE) {
    buffer_position_ = 0;
    UNWRAP_MLAudioResult(MLAudioStartSound(audio_handle_));
  }
#endif
}

void Sound::Stop() {
#ifndef NO_ML_CAPI
  if (audio_handle_ != ML_INVALID_HANDLE) {
    UNWRAP_MLAudioResult(MLAudioStopSound(audio_handle_));
  }
#endif
}

void Sound::SetPos(const XrVector3f &pos) {
#ifndef NO_ML_CAPI
  MLVec3f position{{{pos.x, pos.y, pos.z}}};
  MLQuaternionf orientation{};
  UNWRAP_MLAudioResult(
      MLAudioSetSpatialSoundPosition(audio_handle_, 0, &position));
  UNWRAP_MLAudioResult(
      MLAudioSetSpatialSoundDirection(audio_handle_, 0, &orientation));
#endif
}

void Sound::SetPose(const XrPosef &pose) {
#ifndef NO_ML_CAPI
  MLVec3f position{{{pose.position.x, pose.position.y, pose.position.z}}};
  MLQuaternionf orientation{{{pose.orientation.x, pose.orientation.y,
                              pose.orientation.z, pose.orientation.w}}};
  UNWRAP_MLAudioResult(
      MLAudioSetSpatialSoundPosition(audio_handle_, 0, &position));
  UNWRAP_MLAudioResult(
      MLAudioSetSpatialSoundDirection(audio_handle_, 0, &orientation));
#endif
}

void Sound::CreateAudio() {
#ifndef NO_ML_CAPI
  MLAudioBufferFormat format;
  uint32_t recommended_size;

  UNWRAP_MLAudioResult(MLAudioGetBufferedOutputDefaults(
      channels_, sample_rate_, 1.0, &format, &recommended_size, nullptr));

  MLAudioBufferCallback callback = [](MLHandle handle, void *callback_context) {
    auto *self = reinterpret_cast<Sound *>(callback_context);
    self->FillBuffer();
  };

  format.channel_count = channels_;
  format.samples_per_second = sample_rate_;
  format.bits_per_sample = bits_per_sample_;
  format.valid_bits_per_sample = bits_per_sample_;
  format.sample_format = MLAudioSampleFormat_Int;
  format.channel_format = MLAudioChannelFormat_Default;

  UNWRAP_MLAudioResult(MLAudioCreateSoundWithBufferedOutput(
      &format, recommended_size, callback, (void *)this, &audio_handle_));

  UNWRAP_MLAudioResult(MLAudioSetSpatialSoundEnable(audio_handle_, true));
#endif
}

bool Sound::FillBuffer() {
#ifndef NO_ML_CAPI
  MLAudioBuffer buffer = {};
  MLResult result;
  result = MLAudioGetOutputBuffer(audio_handle_, &buffer);
  if (MLAudioResult_BufferNotReady == result) {
    return false;
  }
  UNWRAP_MLAudioResult(result);
  size_t bytes_to_copy = std::min(static_cast<size_t>(buffer.size),
                                  raw_buffer_.size() - buffer_position_);
  buffer.size = bytes_to_copy;
  if (bytes_to_copy > 0) {
    memcpy(buffer.ptr, raw_buffer_.data() + buffer_position_, bytes_to_copy);
  } else {
    if (looping_) {
      buffer_position_ = 0;
    } else {
      Stop();
    }
  }
  buffer_position_ += buffer.size;
  UNWRAP_MLAudioResult(MLAudioReleaseOutputBuffer(audio_handle_));
#endif
  return true;
}

void Sound::DestroyAudio() {
#ifndef NO_ML_CAPI
  if (audio_handle_ != ML_INVALID_HANDLE) {
    Stop();
    UNWRAP_MLAudioResult(MLAudioDestroySound(audio_handle_));
  }
#endif
}
