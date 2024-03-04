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

#include <chrono>
#include <map>
#include <memory>
#include <tuple>

#include "../AssetManager.h"
#include "../Scene/Node.h"
#include "Component.h"

#ifdef XR_USE_PLATFORM_ANDROID
#include <android/asset_manager.h>
#endif

namespace tinygltf {
class Model;
class Node;
struct Mesh;
struct Primitive;
struct Material;
}  // namespace tinygltf
namespace ml::Components {

class GLTFNodeId : public IComponent {
 public:
  GLTFNodeId(uint32_t id) : id_(id) {
  }
  inline uint32_t Id() const {
    return id_;
  }

 private:
  uint32_t id_;
};
using GLTFNodeIdPtr = std::shared_ptr<Components::GLTFNodeId>;
}  // namespace ml::Components

namespace ml {

/*! \brief Animation Class for GLTF objects. */
class IGLTFAnimation {
 public:
  virtual ~IGLTFAnimation() {
  }
  /*! \brief Returns true if the animation is currently playing. */
  virtual bool IsPlaying() const = 0;
  /*! \brief Plays the animation from the last position. */
  virtual void Play() = 0;
  /*! \brief Pauses the animation. */
  virtual void Pause() = 0;
  /*! \brief Stops the animation. Resets the position to the start. */
  virtual void Stop() = 0;
  /*! \brief Controls the loop behavior of the animation. */
  virtual void SetLooping(bool loop) = 0;
  /*! \brief Returns the loop behavior of the animation.
   *
   * true/false only indicates that IF the animation was playing
   * if it would loop. It does not indicate if the animation is
   * currently playing.
   */
  virtual bool IsLooping() const = 0;
  /*! \brief Name of the animation. */
  virtual const std::string &Name() const = 0;
  /*! \brief Duration of the animation in milliseconds. */
  virtual int64_t Duration() const = 0;
  /*! \brief Play animation for given amount of time (in milliseconds).
   *
   * Animation may loop if given time exceeds duration.
   * Animation will be played from the beginning.
   * Animation will be reset to the start after stopping.
   */
  virtual void PlayFor(int64_t time) = 0;
};
using GLTFAnimationPtr = std::shared_ptr<IGLTFAnimation>;

class GLTFBufferViewTracker {
 public:
  GLTFBufferViewTracker(const tinygltf::Model *model) : model_(model) {
  }
  const uint8_t *Register(int buffer_view);
  const uint8_t *Get(int buffer_view) const;

 protected:
  const tinygltf::Model *model_;
  std::map<int, std::vector<uint8_t>> buffer_views;
  const std::vector<uint8_t> empty_;
};

namespace Components {

class GLTF;
/*! Shared Pointer type of the GLTF Component. */
using GLTFPtr = std::shared_ptr<Components::GLTF>;

// forward declaration.
class TextureData;

/*! GLTF Model Import Component.
 *
 * This Component imports GLTF files.
 * https://www.khronos.org/gltf/
 *
 * Current Limitations:
 *
 * No skins, morphing and no cameras.
 *
 * Note animations by default do -not- run, query the animations
 * using the Animations method and enable/disable as needed.
 *
 */
class GLTF : public IComponent {
 public:
  /*! \brief GLTF constructor.
   *
   * @param node to attach the meshes to
   * @param model is the GLTF file as imported by tinygltf
   */
  GLTF(Scene::Node *node, std::unique_ptr<tinygltf::Model> &model);

#ifdef XR_USE_PLATFORM_ANDROID
  /*! \brief On Android GLTF needs the Android Asset Manager.
   *
   * The application framework takes care of setting this.
   */
  static void SetAssetManager(AAssetManager *asset_manager);
#endif

  /*! \brief GLTF model factory.
   *
   * @param data pointer to the data
   * @param size size of the data
   * @return GLTFP Component and newly created node.
   *
   * The data is expected to be a binary GLTF file.
   *
   */
  static std::tuple<GLTFPtr, Scene::Node *> Factory(const char *data,
                                                    size_t size);

  /*! \brief GLTF model factory.
   *
   * @param filename filename of the GLTF model to load.
   * @return GLTFP Component and newly created node.
   *
   * Make sure the filename ends with .gltf or .glb so the library
   * can decide if this is a binary or ascii file.
   */
  static std::tuple<GLTFPtr, Scene::Node *> Factory(const char *filename);

  /*! \brief Returns the animations. */
  const std::vector<GLTFAnimationPtr> &Animations() {
    return animations_;
  }

  /*! \brief Updates animations. */
  void OnUpdate();

  bool Shareable() const override {
    return false;
  }
  IComponentPtr DeepCopy(ComponentHolder *context) const override;

 private:
  GLTF(const GLTF &gltf, Scene::Node *node);
  std::unique_ptr<tinygltf::Model> model_;
  std::vector<Scene::Node *> nodes_;
  std::vector<GLTFAnimationPtr> animations_;
  std::chrono::time_point<std::chrono::steady_clock> creation_time_;
  std::map<int, std::shared_ptr<Components::Material>> materials_;
  std::map<int, std::shared_ptr<ml::Components::TextureData>> textures_;
  GLTFBufferViewTracker buffer_view_tracker_;
  void LoadAnimations();

  static void LoadNormals(Components::Mesh &mesh, tinygltf::Model &model,
                          int accessor_index);
  static void LoadPositions(Components::Mesh &mesh, tinygltf::Model &model,
                            int accessor_index);
  static void LoadTangents(Components::Mesh &mesh, tinygltf::Model &model,
                           int accessor_index);
  static void LoadTextureCoordinates(Components::Mesh &mesh,
                                     tinygltf::Model &model,
                                     int accessor_index);

  std::shared_ptr<ml::Components::TextureData> LoadTexture(
      int texture_index, const tinygltf::Material &material);

  std::shared_ptr<Components::Material> LoadMaterial(
      const tinygltf::Material &mat);
  void LoadMaterials();

  void BindMesh(Scene::Node *scene_node, tinygltf::Mesh &mesh);
  void BindModelNodes(Scene::Node *scene_node, tinygltf::Model &model,
                      int node_index);
  void BindScenes(Scene::Node *node);
};

}  // namespace Components
}  // namespace ml