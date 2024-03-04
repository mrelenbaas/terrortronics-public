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

#include "../../include/app_framework/Components/GLTF.h"

#include "../../include/app_framework/Components/Mesh.h"

#ifdef XR_USE_PLATFORM_ANDROID
#define TINYGLTF_ANDROID_LOAD_FROM_ASSETS
#endif
// We're using STB already in this project, make sure
// tiny gltf doesn't load it again.
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_IMPLEMENTATION
#include <stb_image.h>
#include <tiny_gltf.h>

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

#include "../include/app_framework/Components/GLTFAnimation.h"
#include "../include/app_framework/Components/Texture.h"

using namespace tinygltf;
using namespace ml::Components;
using namespace ml::Linear;

// forward declaration.
bool LoadImageData2(Image *image, int image_idx, std::string *err,
                    std::string *warn, int req_width, int req_height,
                    const unsigned char *bytes, int size, void *user_data);

static bool HasEnding(std::string const &full_string,
                      std::string const &ending) {
  if (full_string.length() >= ending.length()) {
    return (0 == full_string.compare(full_string.length() - ending.length(),
                                     ending.length(), ending));
  } else {
    return false;
  }
}

std::tuple<std::shared_ptr<GLTF>, ml::Scene::Node *> GLTF::Factory(
    const char *data, size_t size) {
  TinyGLTF loader;
  auto model = std::make_unique<tinygltf::Model>();
  std::string err;
  std::string warn;
  bool result = loader.LoadBinaryFromMemory(model.get(), &err, &warn,
                                            (const unsigned char *)data, size);
  if (!err.empty()) {
    ALOGE("Error loading binary - %s", err.c_str());
  }
  if (!warn.empty()) {
    ALOGE("Warning loading binary - %s", err.c_str());
  }
  if (!result) {
    return std::make_tuple(nullptr, nullptr);
  }
  auto node = new Scene::Node();
  auto gltf = std::make_shared<GLTF>(node, model);
  node->AddComponent(gltf);
  return std::make_tuple(gltf, node);
}

std::tuple<std::shared_ptr<GLTF>, ml::Scene::Node *> GLTF::Factory(
    const char *filename) {
  TinyGLTF loader;
  auto model = std::make_unique<tinygltf::Model>();
  std::string err;
  std::string warn;
  bool result = false;

  loader.SetImageLoader(LoadImageData2, nullptr);

  if (HasEnding(filename, ".gltf")) {
    result = loader.LoadASCIIFromFile(model.get(), &err, &warn, filename);
  } else if (HasEnding(filename, ".glb")) {
    result = loader.LoadBinaryFromFile(model.get(), &err, &warn, filename);
  } else {
    ALOGE("Unable to load %s", filename);
    return std::make_tuple(nullptr, nullptr);
  }
  if (!err.empty()) {
    ALOGE("Error loading %s - %s", filename, err.c_str());
  }
  if (!warn.empty()) {
    ALOGE("Warning loading %s - %s", filename, err.c_str());
  }
  if (!result) {
    return std::make_tuple(nullptr, nullptr);
  }
  auto node = new Scene::Node();
  auto gltf = std::make_shared<GLTF>(node, model);
  node->AddComponent(gltf);
  return std::make_tuple(gltf, node);
}

void GLTF::LoadAnimations() {
  for (const auto &animation : model_->animations) {
    auto a = std::make_shared<GLTFAnimation>(buffer_view_tracker_, *model_,
                                             animation, nodes_);
    animations_.push_back(a);
  }
}

void GLTF::LoadPositions(Components::Mesh &mesh, tinygltf::Model &model,
                         int accessor_index) {
  tinygltf::Accessor accessor = model.accessors[accessor_index];
  auto buffer_view = model.bufferViews[accessor.bufferView];
  const tinygltf::Buffer &buffer = model.buffers[buffer_view.buffer];
  if (accessor.type != TINYGLTF_TYPE_VEC3) {
    ALOGE("Unsupported position coordinate type, expecting VEC2");
    return;
  }
  if (accessor.componentType != GL_FLOAT) {
    ALOGE("Unsupported position data type, expecting floats");
  }

  if (mesh.vertices.size() != accessor.count) {
    if (!mesh.vertices.empty()) {
      ALOGE("Redefining length of mesh,.. this is not good.");
      return;
    }
    mesh.vertices.resize(accessor.count);
  }

  auto &vertices = mesh.vertices;
  auto *data =
      (const XrVector3f *)(buffer.data.data() + buffer_view.byteOffset +
                           accessor.byteOffset);
  for (size_t i = 0; i < accessor.count; i++) {
    vertices[i].pos = *data++;
  }
}

void GLTF::LoadNormals(Components::Mesh &mesh, tinygltf::Model &model,
                       int accessor_index) {
  tinygltf::Accessor accessor = model.accessors[accessor_index];
  auto buffer_view = model.bufferViews[accessor.bufferView];
  const tinygltf::Buffer &buffer = model.buffers[buffer_view.buffer];
  if (accessor.type != TINYGLTF_TYPE_VEC3) {
    ALOGE("Unsupported normal coordinate type, expecting VEC2");
    return;
  }
  if (accessor.componentType != GL_FLOAT) {
    ALOGE("Unsupported normal data type, expecting floats");
  }

  if (mesh.vertices.size() != accessor.count) {
    if (!mesh.vertices.empty()) {
      ALOGE("Redefining length of mesh,.. this is not good.");
      return;
    }
    mesh.vertices.resize(accessor.count);
  }

  auto &vertices = mesh.vertices;
  auto *data = (const XrVector3f *)(buffer.data.data() + accessor.byteOffset +
                                    buffer_view.byteOffset);
  for (size_t i = 0; i < accessor.count; i++) {
    vertices[i].normal = *data++;
  }
}

void GLTF::LoadTextureCoordinates(Components::Mesh &mesh,
                                  tinygltf::Model &model, int accessor_index) {
  tinygltf::Accessor accessor = model.accessors[accessor_index];
  auto buffer_view = model.bufferViews[accessor.bufferView];
  const tinygltf::Buffer &buffer = model.buffers[buffer_view.buffer];
  if (accessor.type != TINYGLTF_TYPE_VEC2) {
    ALOGE("Unsupported texture coordinate type, expecting VEC2");
    return;
  }
  if (accessor.componentType != GL_FLOAT) {
    ALOGE("Unsupported texture data type, expecting floats");
  }
  if (mesh.vertices.size() != accessor.count) {
    if (!mesh.vertices.empty()) {
      ALOGE("Redefining length of mesh,.. this is not good.");
      return;
    }
    mesh.vertices.resize(accessor.count);
  }

  auto &vertices = mesh.vertices;
  auto *data = (const XrVector2f *)(buffer.data.data() + accessor.byteOffset +
                                    buffer_view.byteOffset);
  for (size_t i = 0; i < accessor.count; i++) {
    vertices[i].uv = *data++;
  }
}

void GLTF::LoadTangents(Components::Mesh &mesh, tinygltf::Model &model,
                        int accessor_index) {
  tinygltf::Accessor accessor = model.accessors[accessor_index];
  auto buffer_view = model.bufferViews[accessor.bufferView];
  const tinygltf::Buffer &buffer = model.buffers[buffer_view.buffer];
  if (accessor.type != TINYGLTF_TYPE_VEC4) {
    ALOGE("Unsupported tangent coordinate type, expecting VEC4");
    return;
  }
  if (accessor.componentType != GL_FLOAT) {
    ALOGE("Unsupported tangent data type, expecting floats");
  }
  if (mesh.vertices.size() != accessor.count) {
    if (!mesh.vertices.empty()) {
      ALOGE("Redefining length of mesh,.. this is not good.");
      return;
    }
    mesh.vertices.resize(accessor.count);
  }

  auto &vertices = mesh.vertices;
  auto *data = (const XrColor4f *)(buffer.data.data() + accessor.byteOffset +
                                   buffer_view.byteOffset);
  for (size_t i = 0; i < accessor.count; i++) {
    vertices[i].color = *data++;
  }
}

std::shared_ptr<ml::Components::TextureData> GLTF::LoadTexture(
    int texture_index, const tinygltf::Material &material) {
  if (texture_index >= static_cast<int>(model_->textures.size()) ||
      texture_index < 0) {
    return nullptr;
  }

  // see if we already have this texture.
  auto tex_it = textures_.find(texture_index);
  if (tex_it != textures_.end()) {
    ALOGV("Reusing Texture %d", texture_index);
    return tex_it->second;
  }

  auto texture = model_->textures[texture_index];

  if (texture.source >= static_cast<int>(model_->images.size()) ||
      texture.source < 0) {
    return nullptr;
  }

  ITexture::ShaderSettings shader_settings{};

  if (texture.sampler >= 0 &&
      texture.sampler < static_cast<int>(model_->samplers.size())) {
    const auto &sampler = model_->samplers[texture.sampler];
    shader_settings.magnification =
        ITexture::ShaderSettings::GLToFilter(sampler.magFilter);
    shader_settings.minification =
        ITexture::ShaderSettings::GLToFilter(sampler.minFilter);
    shader_settings.u_wrap = ITexture::ShaderSettings::GLToWrap(sampler.wrapS);
    shader_settings.v_wrap = ITexture::ShaderSettings::GLToWrap(sampler.wrapT);
  }

  auto image = model_->images[texture.source];
  bool delete_buffer = false;

  unsigned char *buffer;
  size_t buffer_size = 0;

  if (image.component == 3) {
    buffer_size = image.width * image.height * 4;
    buffer = new unsigned char[buffer_size];
    unsigned char *rgba = buffer;
    unsigned char *rgb = image.image.data();
    for (int i = 0; i < image.width * image.height; ++i) {
      memcpy(rgba, rgb, sizeof(unsigned char) * 3);
      rgba += 4;
      rgb += 3;
    }
    delete_buffer = true;
  } else {
    buffer = image.image.data();
    buffer_size = image.image.size();
  }

  auto t = std::make_shared<Components::TextureData>(
      (const char *)buffer, buffer_size, image.width, image.height);

  t->UpdateShader(shader_settings);

  if (delete_buffer) {
    delete[] buffer;
  }

  textures_[texture_index] = t;  // keep it around it might be re-used.
  return t;
}

std::shared_ptr<ml::Components::Material> GLTF::LoadMaterial(
    const tinygltf::Material &mat) {
  auto material = std::make_shared<Material>();
  auto val_it = mat.values.find("baseColorFactor");
  if (val_it != mat.values.end()) {
    material->base_color =
        Linear::CreateColor(val_it->second.ColorFactor().data());
    material->use_material = true;
  } else {
    material->base_color = XrColor4f{1.0f, 1.0f, 1.0f, 1.0f};
  }

  val_it = mat.values.find("metallicFactor");
  if (val_it != mat.values.end()) {
    material->metallic = (float)val_it->second.Factor();
    material->use_material = true;
  } else {
    material->metallic = 1.0;
  }

  val_it = mat.values.find("roughnessFactor");
  if (val_it != mat.values.end()) {
    material->roughness = (float)val_it->second.Factor();
    material->use_material = true;
  } else {
    material->roughness = 1.0f;
  }

  // Load the textures.
  material->color_texture =
      LoadTexture(mat.pbrMetallicRoughness.baseColorTexture.index, mat);
  material->metallic_roughness_texture =
      LoadTexture(mat.pbrMetallicRoughness.metallicRoughnessTexture.index, mat);
  material->normal_texture = LoadTexture(mat.normalTexture.index, mat);

  material->occlusion_texture = LoadTexture(mat.occlusionTexture.index, mat);
  material->occlusion_strength = (float)mat.occlusionTexture.strength;

  material->emissive_texture = LoadTexture(mat.emissiveTexture.index, mat);
  material->emissive_factor =
      XrColor4f{(float)mat.emissiveFactor[0], (float)mat.emissiveFactor[1],
                (float)mat.emissiveFactor[2], 1.0f};

  return material;
}

void GLTF::BindMesh(Scene::Node *scene_node, tinygltf::Mesh &mesh) {
  // one gltf node can have multiple meshes
  // our tree only allows one mesh per node, so create subnodes for the
  // meshes.

  // todo deal with byte stride
  for (auto primitive : mesh.primitives) {
    if (primitive.mode != TINYGLTF_MODE_TRIANGLES) {
      ALOGE("Sorry we only support triangle meshes.");
      continue;
    }
    auto mesh_node = new Scene::Node();
    scene_node->AddChild(mesh_node);

    std::shared_ptr<ml::Components::Material> material;
    auto mat_it = materials_.find(primitive.material);
    if (mat_it != materials_.end()) {
      material = mat_it->second;
    } else {
      material = std::make_shared<ml::Components::Material>();
      material->use_material = false;
    }

    auto mesh_component = std::make_shared<Components::Mesh>(material);

    mesh_node->AddComponent(mesh_component);
    mesh_component->type = ml::Components::Mesh::PBR;

    tinygltf::Accessor index_accessor = model_->accessors[primitive.indices];

    {
      auto &indices = mesh_component->indices;
      auto buffer_view = model_->bufferViews[index_accessor.bufferView];
      const tinygltf::Buffer &buffer = model_->buffers[buffer_view.buffer];

      indices.resize(index_accessor.count);
      //
      switch (index_accessor.componentType) {
        case GL_UNSIGNED_BYTE: {
          auto *data =
              (const uint8_t *)(buffer.data.data() + buffer_view.byteOffset +
                                index_accessor.byteOffset);
          for (size_t i = 0; i < index_accessor.count; i++) {
            indices[i] = *data;
            data++;
          }
          break;
        }
        case GL_UNSIGNED_SHORT: {
          auto *data =
              (const uint16_t *)(buffer.data.data() + buffer_view.byteOffset +
                                 index_accessor.byteOffset);
          for (size_t i = 0; i < index_accessor.count; i++) {
            indices[i] = *data;
            data++;
          }
          break;
        }
        case GL_UNSIGNED_INT: {
          // TODO do we need to support more?
          ALOGW(
              "indices are using integer, we only support up to 65536 "
              "indices.");
          auto *data =
              (const uint32_t *)(buffer.data.data() + buffer_view.byteOffset +
                                 index_accessor.byteOffset);
          for (size_t i = 0; i < index_accessor.count; i++) {
            indices[i] = uint16_t((*data) & (0xffff));
            data++;
          }
          break;
        }
        default:
          ALOGE("Unsupported index type %d", index_accessor.componentType);
      }
    }

    auto it = primitive.attributes.find("POSITION");
    if (it != primitive.attributes.end()) {
      int buffer_view = it->second;
      LoadPositions(*mesh_component, *model_, buffer_view);
    }

    it = primitive.attributes.find("NORMAL");
    if (it != primitive.attributes.end()) {
      int buffer_view = it->second;
      LoadNormals(*mesh_component, *model_, buffer_view);
    }

    // we only support one set of texture coordinates
    it = primitive.attributes.find("TEXCOORD_0");
    if (it != primitive.attributes.end()) {
      int coordinate_buffer_view = it->second;
      LoadTextureCoordinates(*mesh_component, *model_, coordinate_buffer_view);
    }

    it = primitive.attributes.find("TANGENT");
    if (it != primitive.attributes.end()) {
      int tangent_buffer_view = it->second;
      LoadTangents(*mesh_component, *model_, tangent_buffer_view);
    } else {
      if (mesh_component->material->normal_texture) {
        if (!mesh_component->GenerateTangents()) {
          ALOGE("Unable to generate tangents, removing normal map.");
          mesh_component->material->normal_texture
              .reset();  // no tangents no normals.
        }
      }
    }
  }
}

// bind models
void GLTF::BindModelNodes(Scene::Node *scene_node, tinygltf::Model &model,
                          int node_index) {
  const tinygltf::Node &node = model.nodes[node_index];
  nodes_[node_index] = scene_node;
  auto ni = std::make_shared<GLTFNodeId>(node_index);
  scene_node->AddComponent(ni);
  scene_node->SetName(node.name);
  if ((node.mesh >= 0) &&
      (node.mesh >= 0 && node.mesh < static_cast<int>(model.meshes.size()))) {
    if (node.translation.size() == 3) {
      scene_node->SetTranslation((float)node.translation[0],
                                 (float)node.translation[1],
                                 (float)node.translation[2]);
    }

    if (node.rotation.size() == 4) {
      scene_node->SetRotation((float)node.rotation[0], (float)node.rotation[1],
                              (float)node.rotation[2], (float)node.rotation[3]);
    }

    if (node.scale.size() == 3) {
      scene_node->SetScale((float)node.scale[0], (float)node.scale[1],
                           (float)node.scale[2]);
    }

    if (node.matrix.size() == 16) {
      XrMatrix4x4f transform;
      XrCreateIdentity(transform);

      for (size_t i = 0; i < 16; i++) {
        transform.m[i] = (float)node.matrix[i];
      }
      XrQuaternionf rotate;
      XrVector3f scale;
      XrVector3f translation;
      XrGetRotation(rotate, transform);
      XrGetScale(scale, transform);
      XrGetTranslation(translation, transform);
      scene_node->SetRotation(rotate);
      scene_node->SetTranslation(translation);
      scene_node->SetScale(scale);
    }

    BindMesh(scene_node, model.meshes[node.mesh]);
  }

  for (size_t i = 0; i < node.children.size(); i++) {
    assert((node.children[i] >= 0) &&
           (node.children[i] < static_cast<int>(model.nodes.size())));
    Scene::Node *child = new Scene::Node();
    scene_node->AddChild(child);
    BindModelNodes(child, model, node.children[i]);
  }
}

void GLTF::BindScenes(Scene::Node *node) {
  const tinygltf::Scene &scene = model_->scenes[model_->defaultScene];

  nodes_.clear();
  nodes_.resize(model_->nodes.size());

  for (size_t i = 0; i < scene.nodes.size(); ++i) {
    auto node_idx = scene.nodes[i];
    assert((node_idx >= 0) &&
           (node_idx < static_cast<int>(model_->nodes.size())));

    auto scene_node = new Scene::Node();
    node->AddChild(scene_node);
    BindModelNodes(scene_node, *model_.get(), node_idx);
  }
}

GLTF::GLTF(Scene::Node *node, std::unique_ptr<tinygltf::Model> &model)
    : model_(std::move(model)), buffer_view_tracker_(model_.get()) {
  LoadMaterials();
  BindScenes(node);
  LoadAnimations();
  creation_time_ = std::chrono::steady_clock::now();
  model_.reset();
}

#ifdef XR_USE_PLATFORM_ANDROID
void GLTF::SetAssetManager(AAssetManager *manager) {
  asset_manager = manager;
}
#endif

void GLTF::OnUpdate() {
  std::chrono::duration duration =
      std::chrono::steady_clock::now() - creation_time_;
  int64_t t =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  for (auto &anim : animations_) {
    std::static_pointer_cast<GLTFAnimation>(anim)->Tick(t);
  }
}

void GLTF::LoadMaterials() {
  for (size_t i = 0; i < model_->materials.size(); i++) {
    const auto &mat = model_->materials[i];
    materials_[i] = LoadMaterial(mat);
  }
}

GLTF::GLTF(const GLTF &gltf, Scene::Node *node)
    : buffer_view_tracker_(gltf.buffer_view_tracker_) {
  materials_ = gltf.materials_;
  textures_ = gltf.textures_;
  creation_time_ = gltf.creation_time_;

  nodes_.resize(gltf.nodes_.size(), nullptr);
  std::function<void(Scene::Node *)> recurse;
  recurse = [this, &recurse](Scene::Node *node) {
    auto c = node->GetComponent<GLTFNodeId>();
    if (c) {
      nodes_[c->Id()] = node;
    }
    for (auto &child : node->Children()) {
      recurse(child);
    }
  };
  recurse(node);
  for (auto target : nodes_) {
    if (target == nullptr) {
      ALOGE(
          "Unexpected nullptr found in GLTF node list, things might not work "
          "properly.");
    }
  }
  for (auto &anim : gltf.animations_) {
    auto a = std::dynamic_pointer_cast<GLTFAnimation>(anim);
    animations_.push_back(a->DeepCopy(buffer_view_tracker_, nodes_));
  }
}

IComponentPtr GLTF::DeepCopy(ComponentHolder *context) const {
  Scene::Node *node = dynamic_cast<Scene::Node *>(context);
  GLTF *g = new GLTF(*this, node);
  return GLTFPtr(g);
}

bool LoadImageData2(Image *image, int image_idx, std::string *err,
                    std::string *warn, int req_width, int req_height,
                    const unsigned char *bytes, int size, void *) {
  (void)warn;

  int w = 0, h = 0, comp = 0, req_comp = 0;

  unsigned char *data = nullptr;

  // preserve_channels true: Use channels stored in the image file.
  // false: force 32-bit textures for common Vulkan compatibility. It appears
  // that some GPU drivers do not support 24-bit images for Vulkan
  req_comp = 4;  // option.preserve_channels ? 0 : 4;
  int bits = 8;
  int pixel_type = TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE;

  // It is possible that the image we want to load is a 16bit per channel image
  // We are going to attempt to load it as 16bit per channel, and if it worked,
  // set the image data accodingly. We are casting the returned pointer into
  // unsigned char, because we are representing "bytes". But we are updating
  // the Image metadata to signal that this image uses 2 bytes (16bits) per
  // channel:
  if (stbi_is_16_bit_from_memory(bytes, size)) {
    data = reinterpret_cast<unsigned char *>(
        stbi_load_16_from_memory(bytes, size, &w, &h, &comp, req_comp));
    if (data) {
      bits = 16;
      pixel_type = TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT;
    }
  }

  // at this point, if data is still NULL, it means that the image wasn't
  // 16bit per channel, we are going to load it as a normal 8bit per channel
  // mage as we used to do:
  // if image cannot be decoded, ignore parsing and keep it by its path
  // don't break in this case
  // FIXME we should only enter this function if the image is embedded. If
  // image->uri references
  // an image file, it should be left as it is. Image loading should not be
  // mandatory (to support other formats)
  if (!data) data = stbi_load_from_memory(bytes, size, &w, &h, &comp, req_comp);
  if (!data) {
    // NOTE: you can use `warn` instead of `err`
    if (err) {
      (*err) +=
          "Unknown image format. STB cannot decode image data for image[" +
          std::to_string(image_idx) + "] name = \"" + image->name + "\".\n";
    }
    return false;
  }

  if ((w < 1) || (h < 1)) {
    stbi_image_free(data);
    if (err) {
      (*err) += "Invalid image data for image[" + std::to_string(image_idx) +
                "] name = \"" + image->name + "\"\n";
    }
    return false;
  }

  if (req_width > 0) {
    if (req_width != w) {
      stbi_image_free(data);
      if (err) {
        (*err) += "Image width mismatch for image[" +
                  std::to_string(image_idx) + "] name = \"" + image->name +
                  "\"\n";
      }
      return false;
    }
  }

  if (req_height > 0) {
    if (req_height != h) {
      stbi_image_free(data);
      if (err) {
        (*err) += "Image height mismatch. for image[" +
                  std::to_string(image_idx) + "] name = \"" + image->name +
                  "\"\n";
      }
      return false;
    }
  }

  if (req_comp != 0) {
    // loaded data has `req_comp` channels(components)
    comp = req_comp;
  }

  image->width = w;
  image->height = h;
  image->component = comp;
  image->bits = bits;
  image->pixel_type = pixel_type;
  image->image.resize(static_cast<size_t>(w * h * comp) * size_t(bits / 8));
  std::copy(data, data + w * h * comp * (bits / 8), image->image.begin());
  stbi_image_free(data);

  return true;
}

const uint8_t *ml::GLTFBufferViewTracker::Get(int buffer_view) const {
  auto it = buffer_views.find(buffer_view);
  if (it != buffer_views.end()) {
    return it->second.data();
  }
  return nullptr;
}

const uint8_t *ml::GLTFBufferViewTracker::Register(int buffer_view) {
  auto it = buffer_views.find(buffer_view);
  if (it != buffer_views.end()) {
    return it->second.data();
  }

  if ((buffer_view < 0) || (buffer_view >= (int)model_->bufferViews.size())) {
    ALOGE("BufferView does not exist %d", buffer_view);
    return nullptr;
  }
  const auto &view = model_->bufferViews[buffer_view];
  std::vector<uint8_t> data;
  data.resize(view.byteLength);
  const auto &buffer = model_->buffers[view.buffer];

  memcpy(data.data(), buffer.data.data() + view.byteOffset, view.byteLength);
  buffer_views[buffer_view] = std::move(data);

  return buffer_views[buffer_view].data();
}
