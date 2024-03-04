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

#ifndef NO_ML_CAPI
#include <ml_types.h>
#endif

#include <openxr/openxr.h>

#include <array>
#include <tuple>

#include "../Scene/Node.h"
#include "Component.h"

namespace ml {

namespace Components {

class Sound;
/*! Shared Pointer type of the Sound Component. */
using SoundPtr = std::shared_ptr<Components::Sound>;

/*! \brief A Sound component.
 *
 * Plays a sound in the location of the Node it is attached to.
 *
 */
class Sound : public IComponent {
 public:
  /*! \brief Creates a Sound Component
   *
   * NOTE: the raw_buffer is only taken by reference, it must be kept
   * alive elsewhere. This allows a sound to be loaded in memory once
   * but used in many places.
   *
   * */
  static std::tuple<SoundPtr, Scene::Node *> Factory(
      const std::vector<uint8_t> &raw_buffer, int channels = 1,
      int sample_rate = 44100, int bits_per_sample = 16) {
    auto node = new Scene::Node();
    auto sound = std::make_shared<Sound>(raw_buffer, channels, sample_rate,
                                         bits_per_sample);
    node->AddComponent(sound);
    return std::make_tuple(sound, node);
  }

  /*! \brief Creates a Sound Component
   *
   * NOTE: the raw_buffer is only taken by reference, it must be kept
   * alive elsewhere. This allows a sound to be loaded in memory once
   * but used in many places.
   *
   * */
  Sound(const std::vector<uint8_t> &raw_buffer, int channels = 1,
        int sample_rate = 44100, int bits_per_sample = 16);
  ~Sound();

  /*! \brief Play the sound. */
  void Play();
  /*! \brief Stop the sound. */
  void Stop();

  /*! \brief This is called by the scene graph */
  void SetPos(const XrVector3f &pos);
  /*! \brief This is called by the scene graph */
  void SetPose(const XrPosef &pose);

  /*! \brief Set to true if the sound should loop. */
  inline void SetLooping(bool looping) {
    looping_ = looping;
  }

  /*! \brief Returns true if looping is enabled. */
  inline bool Looping() const {
    return looping_;
  }

  bool Shareable() const override {
    return false;
  }
  IComponentPtr DeepCopy(ComponentHolder *) const override {
    auto sound =
        new Sound(raw_buffer_, channels_, sample_rate_, bits_per_sample_);
    return SoundPtr(sound);
  }

 private:
#ifndef NO_ML_CAPI
  MLHandle audio_handle_;
#endif
  const std::vector<uint8_t> &raw_buffer_;
  size_t buffer_position_ = 0;
  int channels_;
  int sample_rate_;
  int bits_per_sample_;
  bool looping_;

  void CreateAudio();
  void DestroyAudio();

  bool FillBuffer();
};

}  // namespace Components
}  // namespace ml
