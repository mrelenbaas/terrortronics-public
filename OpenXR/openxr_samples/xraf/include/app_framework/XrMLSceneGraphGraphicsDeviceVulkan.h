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

#include <memory>

#include "Scene/Node.h"
#include "XrMLGraphicsDeviceVulkan.h"
#include "app_framework/Components/Material.h"
#include "app_framework/Geometry/Vertex.h"
#include "vulkan/Buffer.h"
#include "vulkan/ImageBuffer.h"
#include "vulkan/MaterialDescriptorSet.h"
#include "vulkan/ShaderModule.h"
#include "vulkan/TextureDescriptorPool.h"
#include "vulkan/UBO.h"
#include "vulkan/VulkanGui.h"

namespace ml {

class XrMLSceneGraphGraphicsDeviceVulkan : public XrMLGraphicsDeviceVulkan {
 public:
  XrMLSceneGraphGraphicsDeviceVulkan(XrCore *core, Scene::Node *node);
  ~XrMLSceneGraphGraphicsDeviceVulkan();
  bool StartOfRenderLoop() override;
  void RenderFrame() override;
  void RenderView(XrCompositionLayerProjectionView &projection_view,
                  const XrMLSwapChain *color_swap_chain,
                  const XrMLSwapChain *depth_swap_chain,
                  uint32_t view) override;

  IGuiBackend *GetGui() override;
  void UpdateViewMatrix(const std::vector<XrView> &views) override;

 protected:
  Scene::Node *root_node_;
  bool scene_graph_changed_;
  bool scene_has_lights_;

  std::unique_ptr<Vulkan::UBO> ubo_buffer_;
  std::unique_ptr<Vulkan::VulkanImGui> gui_;
  std::vector<std::shared_ptr<ml::Vulkan::MaterialDescriptorSet>>
      native_texture_materials_;  // native materials need updating before
                                  // rendering begins.

  struct PipelineInfo {
    Vulkan::TextureDescriptorPool::PipelineLayoutType pipeline_layout_type;
    vk::Pipeline pipeline;
    vk::PipelineLayout layout;
    std::unique_ptr<Vulkan::ShaderModule> vertex_shader;
    std::unique_ptr<Vulkan::ShaderModule> fragment_shader;
    std::map<ml::Components::Material::TextureType, Vulkan::ImageBufferPtr>
        default_textures;
    std::shared_ptr<Vulkan::MaterialDescriptorSet>
        default_descriptor_set;  // all empty textures.
  };
  std::map<ml::Components::Mesh::Type, PipelineInfo> pipelines_;
  std::map<Vulkan::TextureDescriptorPool::PipelineLayoutType,
           std::unique_ptr<Vulkan::TextureDescriptorPool>>
      descriptor_pools_;

  void UpdateObjects();
  PipelineInfo CreatePipeline(ml::Components::Mesh::Type type);
  ml::Vulkan::ImageBufferPtr CreateDefaultTexture(
      ml::Components::Material::TextureType texture_type,
      ml::Vulkan::TextureDescriptorPool::PipelineLayoutType
          pipeline_layout_type);
  ml::Vulkan::ImageBufferPtr CheckAndCreateTexture(
      Scene::Node *node, Components::Material::TextureType texture_type,
      Components::ITexturePtr &texture, const Components::Mesh &mesh);
  void UpdateNativeTextures();
};
}  // namespace ml
