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

#include "../../include/app_framework/Components/GLTFAnimation.h"

#include <tiny_gltf.h>

#include <cmath>

#ifndef GL_UNSIGNED_BYTE
#define GL_UNSIGNED_BYTE 0x1401
#endif
#ifndef GL_SHORT
#define GL_SHORT 0x1402
#endif
#ifndef GL_UNSIGNED_SHORT
#define GL_UNSIGNED_SHORT 0x1403
#endif
#ifndef GL_INT
#define GL_INT 0x1404
#endif
#ifndef GL_UNSIGNED_INT
#define GL_UNSIGNED_INT 0x1405
#endif
#ifndef GL_FLOAT
#define GL_FLOAT 0x1406
#endif

using namespace ml;
using namespace ml::Linear;

GLTFAnimation::GLTFAnimation(GLTFBufferViewTracker &buffer_view_tracker,
                             const tinygltf::Model &model,
                             const tinygltf::Animation &animation,
                             const std::vector<Scene::Node *> &nodes)
    : playing_(false),
      loop_(false),
      play_until_(0),
      pause_time_(0),
      last_tick_time_(0),
      duration_(0),
      current_time_(0),
      name_(animation.name) {
  std::vector<std::shared_ptr<GLTFAnimationSampler>> samplers;
  for (const auto &sampler : animation.samplers) {
    auto s = std::make_shared<GLTFAnimationSampler>(buffer_view_tracker, model,
                                                    sampler);

    if (s->Duration() > (float)duration_) {
      duration_ = lround(s->Duration() * 1000.0);
    }
    samplers.push_back(s);
  }

  for (const auto &channel : animation.channels) {
    channels_.push_back(std::make_shared<GLTFAnimationChannel>(
        model, channel, nodes, samplers));
  }
}

void GLTFAnimation::Tick(int64_t time) {
  const auto delta = time - last_tick_time_;
  last_tick_time_ = time;

  if (!playing_) {
    return;
  }

  current_time_ += delta;

  const bool is_playing_until = play_until_ > 0;
  const int end = is_playing_until ? play_until_ : duration_;

  if (current_time_ > end) {
    if (loop_) {
      current_time_ = current_time_ % end;
    }

    if (is_playing_until || !loop_) {
      Stop();
      return;
    }
  }

  const float t = current_time_ * 0.001f;
  for (const auto &channel : channels_) {
    channel->Tick(t);
  }
}

void GLTFAnimation::Reset() {
  for (const auto &channel : channels_) {
    channel->Tick(0.f);
  }
}

GLTFAnimation::GLTFAnimation(const GLTFAnimation &anim,
                             const GLTFBufferViewTracker &buffer_view_tracker,
                             const std::vector<Scene::Node *> &nodes)
    : playing_(anim.playing_),
      loop_(anim.loop_),
      play_until_(anim.play_until_),
      pause_time_(anim.pause_time_),
      last_tick_time_(anim.last_tick_time_),
      duration_(anim.duration_),
      current_time_(anim.current_time_),
      name_(anim.name_) {
  for (const auto &channel : anim.channels_) {
    channels_.push_back(channel->DeepCopy(buffer_view_tracker, nodes));
  }
}

GLTFAnimationPtr GLTFAnimation::DeepCopy(
    const GLTFBufferViewTracker &buffer_view_tracker,
    const std::vector<Scene::Node *> &nodes) {
  GLTFAnimation *anim = new GLTFAnimation(*this, buffer_view_tracker, nodes);
  return ml::GLTFAnimationPtr(anim);
}

GLTFAnimationChannel::GLTFAnimationChannel(
    const tinygltf::Model &model, const ::tinygltf::AnimationChannel &channel,
    const std::vector<Scene::Node *> &nodes,
    const std::vector<std::shared_ptr<GLTFAnimationSampler>> &samplers) {
  assert(channel.sampler >= 0);
  assert(channel.sampler < (int)samplers.size());

  sampler_ = samplers[channel.sampler];
  assert(sampler_ != nullptr);

  target_ = nodes[channel.target_node];
  assert(target_ != nullptr);

  if (channel.target_path == "translation") {
    path_ = Translation;
  } else if (channel.target_path == "rotation") {
    path_ = Rotation;
  } else if (channel.target_path == "scale") {
    path_ = Scale;
  } else {
    ALOGW("Unsupported path %s", channel.target_path.c_str());
    path_ = Unsupported;
  }
}
void GLTFAnimationChannel::Tick(float time) {
  if (target_ == nullptr || sampler_ == nullptr || path_ == Unsupported) {
    return;
  }
  switch (path_) {
    case Translation: {
      auto pos = sampler_->Interpolate<XrVector3f>(time);
      target_->SetTranslation(pos);
      break;
    }
    case Scale: {
      auto scale = sampler_->Interpolate<XrVector3f>(time);
      target_->SetScale(scale);
      break;
    }
    case Rotation: {
      auto rot = sampler_->Interpolate<XrQuaternionf>(time);
      target_->SetRotation(rot);
      break;
    }
    default:
      break;
  }
}

GLTFAnimationChannel::GLTFAnimationChannel(
    const GLTFBufferViewTracker &buffer_view_tracker,
    const std::vector<Scene::Node *> &nodes) {
}
std::shared_ptr<GLTFAnimationChannel> GLTFAnimationChannel::DeepCopy(
    const GLTFBufferViewTracker &buffer_view_tracker,
    const std::vector<Scene::Node *> &nodes) {
  GLTFAnimationChannel *ac =
      new GLTFAnimationChannel(buffer_view_tracker, nodes);
  ac->path_ = path_;

  auto node_id = target_->GetComponent<ml::Components::GLTFNodeId>();
  if (!node_id) {
    ALOGE("No node ID on target node.");
    return {};
  }
  ac->target_ = nodes[node_id->Id()];
  ac->sampler_ = std::shared_ptr<GLTFAnimationSampler>(
      new GLTFAnimationSampler(*sampler_));
  return std::shared_ptr<GLTFAnimationChannel>(ac);
}

GLTFAnimationSampler::GLTFAnimationSampler(
    GLTFBufferViewTracker &buffer_view_tracker, const tinygltf::Model &model,
    const tinygltf::AnimationSampler &sampler)
    : input_buffer_(nullptr),
      output_buffer_(nullptr),
      memorized_start_(0),
      memorized_stop_(1) {
  if (sampler.interpolation == "LINEAR") {
    interpolation_ = Linear;
  } else if (sampler.interpolation == "STEP") {
    interpolation_ = Step;
  } else if (sampler.interpolation == "CUBICSPLINE") {
    interpolation_ = Cubic;
  } else {
    ALOGW("Unsupported interpolation type: %s.", sampler.interpolation.c_str());
    return;
  }

  {
    auto &accessor = model.accessors[sampler.input];
    // auto &view = model.bufferViews[accessor.bufferView];
    // auto &buffer = model.buffers[view.buffer];

    if (accessor.type != TINYGLTF_TYPE_SCALAR) {
      ALOGE("Unexpected Accessor type: %d", accessor.type);
      return;
    }
    if (accessor.componentType != GL_FLOAT) {
      ALOGE("Unexpected data type : %d", accessor.componentType);
      return;
    }

    auto ib = buffer_view_tracker.Register(accessor.bufferView);
    input_buffer_ = (const float *)(ib + accessor.byteOffset);
    input_buffer_count_ = accessor.count;
    if (input_buffer_count_ == 0) {
      memorized_stop_ = 0;
    }
  }

  {
    auto &accessor = model.accessors[sampler.output];
    // auto &view = model.bufferViews[accessor.bufferView];
    // auto &buffer = model.buffers[view.buffer];

    if (!((accessor.type == TINYGLTF_TYPE_VEC3) ||
          (accessor.type == TINYGLTF_TYPE_VEC4))) {
      ALOGE("Unexpected Accessor type: %d", accessor.type);
      return;
    }
    output_buffer_type_ = accessor.type;

    if (accessor.componentType != GL_FLOAT) {
      ALOGE("Unexpected data type : %d", accessor.componentType);
      return;
    }

    auto ob = buffer_view_tracker.Register(accessor.bufferView);
    output_buffer_ = (const float *)(ob + accessor.byteOffset);
    output_buffer_count_ = accessor.count;
  }

  if (interpolation_ == Cubic) {
    // cubic spline has 3x the number of elements.
    if (input_buffer_count_ * 3 != output_buffer_count_) {
      ALOGE("input buffer must equal output buffer / 3");
      input_buffer_ = nullptr;
      output_buffer_ = nullptr;
    }
  } else {
    if (input_buffer_count_ != output_buffer_count_) {
      ALOGE("input buffer must equal output buffer");
      input_buffer_ = nullptr;
      output_buffer_ = nullptr;
    }
  }

  //    if ( output_buffer_type_ == TINYGLTF_TYPE_VEC4) {
  //      for (size_t i = 0; i < input_buffer_count_; i++) {
  //        ALOGE("I = %f", (input_buffer_[i]));
  //      }
  //      for (size_t i = 0; i < input_buffer_count_; i++) {
  //        ALOGE("Q = %s", ToString(((XrQuaternionf *)
  //        output_buffer_)[i]).c_str());
  //      }
  //    }
}

void GLTFAnimationSampler::FindIndex(float time, int &start, int &stop) {
  // typically called with increasing values for time.
  if (time >= input_buffer_[memorized_start_] &&
      time <= input_buffer_[memorized_stop_]) {
    start = memorized_start_;
    stop = memorized_stop_;
    return;
  }

  // Set last keyframe as the default value if there's any error
  stop = input_buffer_count_ - 1;
  start = stop - 1;

  for (size_t i = 1; i < input_buffer_count_; i++) {
    if (time <= input_buffer_[i]) {
      start = i - 1;
      stop = i;
      break;
    }
  }

  memorized_start_ = start;
  memorized_stop_ = stop;
}

template <>
XrQuaternionf ml::GLTFAnimationSampler::Lerp(const XrQuaternionf &from,
                                             const XrQuaternionf &to,
                                             float fraction) {
  XrQuaternionf result;
  XrSlerp(result, from, to, fraction);
  return result;
}

template <>
XrVector3f ml::GLTFAnimationSampler::Lerp(const XrVector3f &from,
                                          const XrVector3f &to,
                                          float fraction) {
  XrVector3f result;
  XrLerp(result, from, to, fraction);
  return result;
}

template <>
XrQuaternionf ml::GLTFAnimationSampler::CubicSpline(int start, int stop,
                                                    const void *data,
                                                    float delta_time,
                                                    float fraction) {
  // https://github.com/KhronosGroup/glTF-Tutorials/blob/master/gltfTutorial/gltfTutorial_007_Animations.md
  // IN TANGENT - VERTEX - OUT_TANGENT
  XrQuaternionf *vec_data = (XrQuaternionf *)data;
  const XrQuaternionf &prev_vertex = vec_data[3 * start + 1];
  const XrQuaternionf &prev_out_tangent = vec_data[3 * start + 2];
  const XrQuaternionf &to_in_tangent = vec_data[3 * stop + 0];
  const XrQuaternionf &to_vertex = vec_data[3 * stop + 1];

  XrQuaternionf prev_tangent;
  XrQuaternionf to_tangent;
  XrScale(prev_tangent, prev_out_tangent, delta_time);
  XrScale(to_tangent, to_in_tangent, delta_time);

  float t = fraction;
  float t2 = t * t;
  float t3 = t2 * t;

  float p1 = (2 * t3 - 3 * t2 + 1);
  float p2 = (t3 - 2 * t2 + t);
  float p3 = (-2 * t3 + 3 * t2);
  float p4 = (t3 - t2);

  XrQuaternionf quat{0.0f, 0.0f, 0.0f, 0.0f};

  XrAddScaled(quat, quat, prev_vertex, p1);
  XrAddScaled(quat, quat, prev_tangent, p2);
  XrAddScaled(quat, quat, to_vertex, p3);
  XrAddScaled(quat, quat, to_tangent, p4);
  XrNormalize(quat, quat);
  return quat;
}

template <>
XrVector3f ml::GLTFAnimationSampler::CubicSpline(int start, int stop,
                                                 const void *data,
                                                 float delta_time,
                                                 float fraction) {
  // https://github.com/KhronosGroup/glTF-Tutorials/blob/master/gltfTutorial/gltfTutorial_007_Animations.md
  // IN TANGENT - VERTEX - OUT_TANGENT
  XrVector3f *vec_data = (XrVector3f *)data;
  const XrVector3f &prev_vertex = vec_data[3 * start + 1];
  const XrVector3f &prev_out_tangent = vec_data[3 * start + 2];
  const XrVector3f &to_in_tangent = vec_data[3 * stop + 0];
  const XrVector3f &to_vertex = vec_data[3 * stop + 1];

  XrVector3f prev_tangent;
  XrVector3f to_tangent;
  XrScale(prev_tangent, prev_out_tangent, delta_time);
  XrScale(to_tangent, to_in_tangent, delta_time);

  float t = fraction;
  float t2 = t * t;
  float t3 = t2 * t;

  float p1 = (2 * t3 - 3 * t2 + 1);
  float p2 = (t3 - 2 * t2 + t);
  float p3 = (-2 * t3 + 3 * t2);
  float p4 = (t3 - t2);
  XrVector3f vec{0.0f, 0.0f, 0.0f};

  XrAddScaled(vec, vec, prev_vertex, p1);
  XrAddScaled(vec, vec, prev_tangent, p2);
  XrAddScaled(vec, vec, to_vertex, p3);
  XrAddScaled(vec, vec, to_tangent, p4);
  return vec;
}