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
#include <tuple>
#include <cmath>

#include "../Scene/Node.h"
#include "GLTF.h"
// https://github.com/KhronosGroup/glTF-Tutorials/blob/master/gltfTutorial/gltfTutorial_007_Animations.md
// https://github.com/KhronosGroup/glTF-Tutorials/blob/master/gltfTutorial/gltfTutorial_006_SimpleAnimation.md
// https://www.khronos.org/registry/glTF/specs/2.0/glTF-2.0.html#reference-animation-sampler
// https://raw.githubusercontent.com/KhronosGroup/glTF/main/specification/2.0/figures/gltfOverview-2.0.0b.png

namespace tinygltf {
class Model;
class Node;
struct AnimationSampler;
struct AnimationChannel;
struct Animation;
}  // namespace tinygltf

namespace ml {

class GLTFAnimationSampler;
class GLTFAnimationChannel;

class GLTFAnimation : public IGLTFAnimation {
 public:
  GLTFAnimation(GLTFBufferViewTracker &buffer_view_tracker,
                const tinygltf::Model &model,
                const tinygltf::Animation &animation,
                const std::vector<Scene::Node *> &nodes);

  void Tick(int64_t time);

  bool IsPlaying() const override {
    return playing_;
  }

  void Play() override {
    playing_ = true;
  }

  void Pause() override {
    if (playing_) {
      playing_ = false;
    }
  }

  void Stop() override {
    playing_ = false;
    play_until_ = 0;
    current_time_ = 0;
    Reset();
  }

  void SetLooping(bool loop) override {
    loop_ = loop;
  }

  bool IsLooping() const override {
    return loop_;
  }

  const std::string &Name() const override {
    return name_;
  }

  int64_t Duration() const override {
    return duration_;
  }

  void PlayFor(int64_t deltatime) override {
    Stop();
    play_until_ = deltatime;
    Play();
  }

  GLTFAnimationPtr DeepCopy(const GLTFBufferViewTracker &buffer_view_tracker,
                            const std::vector<Scene::Node *> &nodes);

 private:
  bool playing_;
  bool loop_;
  int64_t play_until_;
  int64_t pause_time_;
  int64_t last_tick_time_;
  int64_t duration_;
  int64_t current_time_;
  std::string name_;
  GLTFAnimation(const GLTFAnimation &anim,
                const GLTFBufferViewTracker &buffer_view_tracker,
                const std::vector<Scene::Node *> &nodes);
  std::vector<std::shared_ptr<GLTFAnimationChannel>> channels_;

  void Reset();
};

class GLTFAnimationChannel {
 public:
  GLTFAnimationChannel(
      const tinygltf::Model &model, const ::tinygltf::AnimationChannel &channel,
      const std::vector<Scene::Node *> &nodes,
      const std::vector<std::shared_ptr<GLTFAnimationSampler>> &samplers);
  void Tick(float time);
  std::shared_ptr<GLTFAnimationChannel> DeepCopy(
      const GLTFBufferViewTracker &buffer_view_tracker,
      const std::vector<Scene::Node *> &nodes);

 private:
  GLTFAnimationChannel(const GLTFBufferViewTracker &buffer_view_tracker,
                       const std::vector<Scene::Node *> &nodes);
  std::shared_ptr<GLTFAnimationSampler> sampler_;
  ml::Scene::Node *target_;
  enum Path { Unsupported, Translation, Rotation, Scale };
  Path path_;
};

class GLTFAnimationSampler {
 public:
  GLTFAnimationSampler(GLTFBufferViewTracker &buffer_view_tracker,
                       const tinygltf::Model &model,
                       const tinygltf::AnimationSampler &sampler);

  float Duration() const {
    if (input_buffer_ == nullptr) {
      return 0.0f;
    }
    return input_buffer_[input_buffer_count_ - 1];
  }

  template <typename T>
  T Interpolate(float time) {
    if (input_buffer_ == nullptr || output_buffer_ == nullptr) {
      ALOGW("No source buffers");
      return T{};
    }

    // LOOP!
    const float end_time = input_buffer_[input_buffer_count_ - 1];
    time = fmodf(time, end_time);
    int start = 0, stop = 0;
    FindIndex(time, start, stop);

    const auto *out = (T *)(output_buffer_);

    const float start_t = input_buffer_[start];
    const float stop_t = input_buffer_[stop];
    const float delta = stop_t - start_t;
    const float fraction = (time - start_t) / delta;

    T result{};

    switch (interpolation_) {
      case Linear:
        return Lerp<T>(out[start], out[stop], fraction);
      case Step:
        return out[start];
      case Cubic:
        return CubicSpline<T>(start, stop, output_buffer_, delta, fraction);
    }
    return result;
  }

 protected:
  const float *input_buffer_;  // timestamps
  size_t input_buffer_count_;
  const void *output_buffer_;
  size_t output_buffer_count_;
  int output_buffer_type_;

  enum Interpolation { Linear, Step, Cubic };
  int memorized_start_;
  int memorized_stop_;
  void FindIndex(float time, int &start, int &stop);
  Interpolation interpolation_;

  template <typename T>
  T Lerp(const T &from, const T &to, float fraction) {
    return T{};
  }
  template <typename T>
  T CubicSpline(int start, int stop, const void *data, float delta_time,
                float fraction) {
    return T{};
  }
};

}  // namespace ml
