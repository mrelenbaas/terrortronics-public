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

#include "../include/app_framework/XrMLSceneGraphGraphicsDeviceVulkan.h"

#include <backends/imgui_impl_vulkan.h>
#include <imgui.h>

#include "../include/app_framework/Components/GLTF.h"
#include "../include/app_framework/Components/Gui.h"
#include "../include/app_framework/Components/Light.h"
#include "../include/app_framework/Components/Mesh.h"
#include "../include/app_framework/Components/Sound.h"
#include "../include/app_framework/Components/Texture.h"
#include "../include/app_framework/Geometry/Cube.h"
#include "../include/app_framework/Scene/Node.h"
#include "../include/app_framework/vulkan/MaterialDescriptorSet.h"
#include "../include/app_framework/vulkan/NativeImageBuffer.h"
#include "../include/app_framework/vulkan/PushConstants.h"

using namespace ml;
using namespace ml::Linear;

XrMLSceneGraphGraphicsDeviceVulkan::XrMLSceneGraphGraphicsDeviceVulkan(
    XrCore *core, Scene::Node *node)
    : XrMLGraphicsDeviceVulkan(core),
      root_node_(node),
      scene_graph_changed_(true),
      scene_has_lights_(false) {
  root_node_->SetOnSceneGraphChanged(
      [this](Scene::Node *node,
             Scene::Node::SceneGraphChangeOperation operation) {
        this->scene_graph_changed_ = true;

        // TODO mesh update doesn't need to invalidate the whole scene graph.
        // keep a list of changed nodes and only re-process those.
        if (operation == Scene::Node::MESH_UPDATED) {
          // remove our mesh info.
          // we must wait until rendering finishes before we can destroy the
          // buffers buffers.
          WaitForFrameRenderFinished();

          node->RemoveComponent<Vulkan::Buffer>(Vulkan::Buffer::Type::VERTEX);
          node->RemoveComponent<Vulkan::Buffer>(Vulkan::Buffer::Type::INDEX);
          node->RemoveComponent<Vulkan::MaterialDescriptorSet>();
        }
      });
}

XrMLSceneGraphGraphicsDeviceVulkan::~XrMLSceneGraphGraphicsDeviceVulkan() {
  native_texture_materials_.clear();
  gui_.reset();
  ubo_buffer_.reset();
  for (auto &pipeline : pipelines_) {
    device_.destroy(pipeline.second.pipeline);
    device_.destroyPipelineLayout(pipeline.second.layout);
    pipeline.second.fragment_shader.reset();
    pipeline.second.vertex_shader.reset();
  }
  pipelines_.clear();
  descriptor_pools_.clear();
}

void XrMLSceneGraphGraphicsDeviceVulkan::UpdateViewMatrix(
    const std::vector<XrView> &views) {
  for (uint32_t view_idx = 0; view_idx < views.size(); view_idx++) {
    const XrView &view = views[view_idx];

    // PROJECTION
    XrMatrix4x4f proj;
    XrCreateProjectionFov(proj, GRAPHICS_VULKAN, view.fov, core_->GetNearZ(),
                          core_->GetFarZ());
    auto &ubo = ubo_buffer_->Get();
    ubo.view[view_idx].projection_matrix = proj;

    // VIEWCreateTextureImage
    XrMatrix4x4f toView;
    XrVector3f scale{1.f, 1.f, 1.f};
    XrCreateTranslationRotationScale(toView, view.pose.position,
                                     view.pose.orientation, scale);
    XrMatrix4x4f view_matrix;
    XrInvertRigidBody(view_matrix, toView);
    ubo.view[view_idx].view_matrix = view_matrix;
    ubo.view[view_idx].camera_pos = XrVector4f{
        view.pose.position.x, view.pose.position.y, view.pose.position.z, 0.0f};
  }
  ubo_buffer_->Sync();
}

void XrMLSceneGraphGraphicsDeviceVulkan::RenderView(
    XrCompositionLayerProjectionView &projection_view,
    const XrMLSwapChain *color_swap_chain,
    const XrMLSwapChain *depth_swap_chain, uint32_t view) {
  assert(color_swap_chain != nullptr);
  assert(depth_swap_chain != nullptr);

  std::array<vk::ClearValue, 2> clearValues;

  clearValues[0].color.float32[0] = 0.0f;
  clearValues[0].color.float32[1] = 0.0f;
  clearValues[0].color.float32[2] = 0.0f;
  clearValues[0].color.float32[3] = 0.0f;
  clearValues[1].color.float32[0] = 0.0f;
  clearValues[1].color.float32[1] = 0.0f;
  clearValues[1].color.float32[2] = 0.0f;
  clearValues[1].color.float32[3] = 0.0f;
  clearValues[1].depthStencil.depth = 1.0f;
  clearValues[1].depthStencil.stencil = 0;

  auto &cmd_buffer = command_buffers_[view];
  vk::CommandBuffer command_buffer = cmd_buffer;
  cmd_buffer.wait();

  command_buffer.reset();
  command_buffer.begin(vk::CommandBufferBeginInfo());

  // Render the ImGUI buffer only for the first view.
  if (view == 0 && gui_) {
    if (gui_->RenderImGui()) {
      gui_->Render(command_buffer, queue_);
    }
  }

  vk::RenderPassBeginInfo rps({}, {}, {}, clearValues.size(), &clearValues[0]);

  BindRenderPass(view, color_swap_chain, depth_swap_chain, rps);

  command_buffer.beginRenderPass(rps, vk::SubpassContents::eInline);

  ml::Components::Mesh::Type current_pipe = ml::Components::Mesh::NONE;

  size_t light_index = 0;

  auto &UBO = ubo_buffer_->Get();
  if (scene_has_lights_ && view == 0) {
    // disable the lights.
    for (uint32_t i = 0; i < MAX_LIGHTS; i++) {
      UBO.light_sources[i].flags = 0;
    }
  }

  root_node_->VisitNodes(
      true,
      [this, &current_pipe, command_buffer, view, &light_index](
          Scene::Node *node, const XrMatrix4x4f &transform) -> bool {
        if (view == 0) {
          auto gltf = node->GetComponent<Components::GLTF>();
          if (gltf) {
            gltf->OnUpdate();
          }

          // Update Sound Components
          auto sound = node->GetComponent<Components::Sound>();
          if (sound) {
            XrVector3f pos;
            XrVector3f origin{0.0f, 0.0f, 0.0f};
            XrTransform(pos, transform, origin);
            sound->SetPos(pos);
            // should we use the Pose?
          }

          // Check for light
          auto light = node->GetComponent<Components::Light>();
          if (light) {
            if (light_index >= MAX_LIGHTS) {
              ALOGW(
                  "This scene graph supports up to %d lights, all others will "
                  "be ignored.",
                  MAX_LIGHTS);
            } else {
              auto &UBO = ubo_buffer_->Get();
              XrVector4f pos;
              XrVector4f origin{0.0f, 0.0f, 0.0f, 1.0f};
              XrTransform(pos, transform, origin);
              UBO.light_sources[light_index].pos = pos;
              UBO.light_sources[light_index].color = light->Color();
              UBO.light_sources[light_index].flags =
                  ml::Vulkan::LightSource::ENABLED;
              light_index++;
              // lights will sync to UBO on the next frame.
            }
          }
        }

        auto vertex_buffer =
            node->GetComponent<Vulkan::Buffer>(Vulkan::Buffer::Type::VERTEX);

        if (!vertex_buffer) {
          return true;
        }

        auto index_buffer =
            node->GetComponent<Vulkan::Buffer>(Vulkan::Buffer::Type::INDEX);
        auto mesh = node->GetComponent<Components::Mesh>();

        if (mesh->type == ml::Components::Mesh::NONE) {
          return true;
        }

        // TODO Performance optimization, switching pipelines is potentially
        // hard on the hardware, order by pipeline type.

        if (mesh->type != current_pipe) {
          current_pipe = mesh->type;
          command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics,
                                      pipelines_[current_pipe].pipeline);
        }

        auto &pipeline_info = pipelines_[current_pipe];
        if (!pipeline_info.pipeline) {
          ALOGE("Pipeline was nullptr");
        }

        vk::DeviceSize offsets[] = {0};
        command_buffer.bindVertexBuffers(0, 1, vertex_buffer->GetBuffer(),
                                         offsets);
        command_buffer.bindIndexBuffer(*index_buffer->GetBuffer(), 0,
                                       vk::IndexType::eUint16);
        command_buffer.bindDescriptorSets(
            vk::PipelineBindPoint::eGraphics, pipeline_info.layout, 0, 1,
            &ubo_buffer_->DescriptorSet(), 0, nullptr);
        Vulkan::PushConstants push_constants{};

        std::vector<vk::DescriptorSet> set_1_descriptors;

        auto material = node->GetComponent<ml::Vulkan::MaterialDescriptorSet>();
        if (material) {
          if (material->HasImage(Components::Material::COLOR)) {
            push_constants.AddFlag(Vulkan::PushConstants::USE_TEXTURE);
          }

          if (material->HasImage(Components::Material::NORMAL)) {
            push_constants.AddFlag(Vulkan::PushConstants::USE_NORMAL_MAP);
          }
          if (material->HasImage(Components::Material::AO)) {
            push_constants.AddFlag(Vulkan::PushConstants::USE_AO_MAP);
          }
          if (material->HasImage(Components::Material::EMISSIVE)) {
            push_constants.AddFlag(Vulkan::PushConstants::USE_EMISSIVE_MAP);
          }

          command_buffer.bindDescriptorSets(
              vk::PipelineBindPoint::eGraphics, pipeline_info.layout, 1, 1,
              &material->DescriptorSet(), 0, nullptr);
        }

        push_constants.SetView(view);
        push_constants.base_color = mesh->material->base_color;
        if (mesh->material->use_material) {
          push_constants.AddFlag(Vulkan::PushConstants::USE_MATERIAL);
          push_constants.SetMetallic(mesh->material->metallic);
          push_constants.SetRoughness(mesh->material->roughness);
          push_constants.emissive_factor = mesh->material->emissive_factor;
          push_constants.ambient_occlusion_strength =
              mesh->material->occlusion_strength;
        }

        {
          push_constants.model_matrix = transform;
          command_buffer.pushConstants(pipeline_info.layout,
                                       vk::ShaderStageFlagBits::eVertex |
                                           vk::ShaderStageFlagBits::eFragment,
                                       0, sizeof(push_constants),
                                       &push_constants);
        }

        command_buffer.drawIndexed(static_cast<uint32_t>(mesh->indices.size()),
                                   1, 0, 0, 0);

        return true;
      });  // end of visit nodes.

  command_buffer.endRenderPass();
  command_buffer.end();
  vk::SubmitInfo submit_info(0, nullptr, nullptr, 1, &command_buffer);

  queue_.submit(submit_info, cmd_buffer);
}

void XrMLSceneGraphGraphicsDeviceVulkan::UpdateNativeTextures() {
  if (native_texture_materials_.empty()) {
    return;
  }
  // if the native texture needs to update we have to wait for all Command
  // Buffers to be finished with the existing textures.
  command_buffers_[0].wait(false);
  command_buffers_[1].wait(false);

  // reuse one of the existing command buffers
  for (auto &native_texture : native_texture_materials_) {
    native_texture->UpdateIfNative(device_, command_buffers_[0], queue_);
  }
}

void XrMLSceneGraphGraphicsDeviceVulkan::RenderFrame() {
  if (scene_graph_changed_) {
    UpdateObjects();
    scene_graph_changed_ = false;
  }
  UpdateNativeTextures();
}

static std::array<vk::VertexInputBindingDescription, 1>
getBindingDescription() {
  return {{{// positions
            0, sizeof(Geometry::Vertex), vk::VertexInputRate::eVertex}}};
}

static std::array<vk::VertexInputAttributeDescription, 4>
getAttributeDescriptions() {
  return {vk::VertexInputAttributeDescription{
              // pos vec3
              0,
              0,
              vk::Format::eR32G32B32Sfloat,
              offsetof(Geometry::Vertex, pos),
          },
          vk::VertexInputAttributeDescription{
              // normal vec3
              1,
              0,
              vk::Format::eR32G32B32Sfloat,
              offsetof(Geometry::Vertex, normal),
          },
          vk::VertexInputAttributeDescription{
              // uv vec2
              2,
              0,
              vk::Format::eR32G32Sfloat,
              offsetof(Geometry::Vertex, uv),
          },
          vk::VertexInputAttributeDescription{
              // color/tangent vec4
              3,
              0,
              vk::Format::eR32G32B32A32Sfloat,
              offsetof(Geometry::Vertex, color),
          }};
}

XrMLSceneGraphGraphicsDeviceVulkan::PipelineInfo
XrMLSceneGraphGraphicsDeviceVulkan::CreatePipeline(
    ml::Components::Mesh::Type type) {
  XrMLSceneGraphGraphicsDeviceVulkan::PipelineInfo pipeline_info;

  switch (type) {
    case ml::Components::Mesh::PBR: {
      // Setup the shaders
      pipeline_info.pipeline_layout_type = Vulkan::TextureDescriptorPool::PBR;
      pipeline_info.vertex_shader = std::make_unique<Vulkan::ShaderModule>(
          core_, device_, ml::Resources::PBR_VERT);
      pipeline_info.fragment_shader = std::make_unique<Vulkan::ShaderModule>(
          core_, device_, ml::Resources::PBR_FRAG);

      for (uint32_t i = 0; i < Material::TEXTURE_TYPE_COUNT; i++) {
        Material::TextureType type = (Material::TextureType)i;
        pipeline_info.default_textures[type] =
            CreateDefaultTexture(type, pipeline_info.pipeline_layout_type);
      }

      auto mds = std::make_shared<Vulkan::MaterialDescriptorSet>(
          descriptor_pools_[pipeline_info.pipeline_layout_type].get(),
          pipeline_info.default_textures);
      Vulkan::ImageBufferPtr image;

      for (uint32_t i = 0; i < Material::TEXTURE_TYPE_COUNT; i++) {
        Material::TextureType type = (Material::TextureType)i;
        mds->AddImage(type, image);
      }

      mds->FinishSetup(device_);
      pipeline_info.default_descriptor_set = mds;
      break;
    }
    case ml::Components::Mesh::NATIVE_BUFFER: {
      // Setup the shaders
      pipeline_info.pipeline_layout_type =
          Vulkan::TextureDescriptorPool::NATIVE_BUFFER;
      pipeline_info.vertex_shader = std::make_unique<Vulkan::ShaderModule>(
          core_, device_, ml::Resources::SHADER_VERT);
      pipeline_info.fragment_shader = std::make_unique<Vulkan::ShaderModule>(
          core_, device_, ml::Resources::SHADER_FRAG);
      pipeline_info.default_textures[Material::TextureType::COLOR] =
          CreateDefaultTexture(Material::TextureType::COLOR,
                               pipeline_info.pipeline_layout_type);
      auto mds = std::make_shared<Vulkan::MaterialDescriptorSet>(
          descriptor_pools_[pipeline_info.pipeline_layout_type].get(),
          pipeline_info.default_textures);
      Vulkan::ImageBufferPtr image;
      mds->AddImage(Material::TextureType::COLOR, image);
      mds->FinishSetup(device_);
      pipeline_info.default_descriptor_set = mds;
      break;
    }
    default: {
      // Setup the shaders
      pipeline_info.pipeline_layout_type = Vulkan::TextureDescriptorPool::UNLIT;
      pipeline_info.vertex_shader = std::make_unique<Vulkan::ShaderModule>(
          core_, device_, ml::Resources::SHADER_VERT);
      pipeline_info.fragment_shader = std::make_unique<Vulkan::ShaderModule>(
          core_, device_, ml::Resources::SHADER_FRAG);
      pipeline_info.default_textures[Material::TextureType::COLOR] =
          CreateDefaultTexture(Material::TextureType::COLOR,
                               pipeline_info.pipeline_layout_type);
      auto mds = std::make_shared<Vulkan::MaterialDescriptorSet>(
          descriptor_pools_[pipeline_info.pipeline_layout_type].get(),
          pipeline_info.default_textures);
      Vulkan::ImageBufferPtr image;
      mds->AddImage(Material::TextureType::COLOR, image);
      mds->FinishSetup(device_);
      pipeline_info.default_descriptor_set = mds;
    }
  }

  auto bindingDescription = getBindingDescription();
  auto attributeDescriptions = getAttributeDescriptions();
  vk::PolygonMode mode = vk::PolygonMode::eFill;
  vk::PrimitiveTopology topology = vk::PrimitiveTopology::eTriangleList;
  vk::CullModeFlags cull_mode = vk::CullModeFlagBits::eBack;
  switch (type) {
    case ml::Components::Mesh::PBR:
    case ml::Components::Mesh::NATIVE_BUFFER:
    case ml::Components::Mesh::TRIANGLE:
      mode = vk::PolygonMode::eFill;
      cull_mode = vk::CullModeFlagBits::eBack;
      topology = vk::PrimitiveTopology::eTriangleList;
      break;
    case ml::Components::Mesh::TRIANGLE_WIREFRAME:
      mode = vk::PolygonMode::eLine;  // validation warning, but it still works!
      cull_mode = vk::CullModeFlagBits::eNone;
      topology = vk::PrimitiveTopology::eTriangleList;
      break;
    case ml::Components::Mesh::LINES:
      mode = vk::PolygonMode::eLine;
      cull_mode = vk::CullModeFlagBits::eNone;
      topology = vk::PrimitiveTopology::eLineList;
      break;
    case ml::Components::Mesh::LINE_STRIP:
      mode = vk::PolygonMode::eLine;
      cull_mode = vk::CullModeFlagBits::eNone;
      topology = vk::PrimitiveTopology::eLineStrip;
      break;
    default:
      throw std::runtime_error("Unknown mesh type");
  }
  cull_mode = vk::CullModeFlagBits::eNone;
  // Define the Pipeline!
  vk::PipelineVertexInputStateCreateInfo vertex_input_state{
      {},
      static_cast<uint32_t>(bindingDescription.size()),
      bindingDescription.data(),
      static_cast<uint32_t>(attributeDescriptions.size()),
      attributeDescriptions.data()};

  vk::PipelineInputAssemblyStateCreateInfo input_assembly{{}, topology, false};

  vk::Viewport viewport{0.0f,
                        0.0f,
                        static_cast<float>(size_.width),
                        static_cast<float>(size_.height),
                        0.0f,
                        1.0f};

  vk::Rect2D scissor{{}, size_};

  vk::PipelineViewportStateCreateInfo viewport_state{
      {}, 1, &viewport, 1, &scissor};

  vk::PipelineRasterizationStateCreateInfo rasterizer{
      {},    false, false, mode, cull_mode, vk::FrontFace::eCounterClockwise,
      false, 0.0f,  0.0f,  0.0f, 1.0f};

  vk::PipelineMultisampleStateCreateInfo multisampling{
      {},
      vk::SampleCountFlagBits::e1,
      false,
      1.0f,
  };

  vk::PipelineColorBlendAttachmentState color_blend_attachment{
      true,
      vk::BlendFactor::eSrcAlpha,
      vk::BlendFactor::eOneMinusSrcAlpha,
      vk::BlendOp::eAdd,
      vk::BlendFactor::eOne,
      vk::BlendFactor::eZero,
      vk::BlendOp::eAdd,
      vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
          vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA};

  vk::PipelineColorBlendStateCreateInfo color_blending{
      {}, false, vk::LogicOp::eCopy, 1, &color_blend_attachment};

  vk::PipelineDepthStencilStateCreateInfo depth_stencil_create_info{
      {}, true, true, vk::CompareOp::eLess, false, false, {}, {}, 0.0f, 1.0f};

  vk::PushConstantRange pcr = {
      vk::ShaderStageFlagBits::eVertex | vk::ShaderStageFlagBits::eFragment, 0,
      sizeof(Vulkan::PushConstants)};

  auto ubo_descriptor_set_layout = ubo_buffer_->Layout();
  std::vector<vk::DescriptorSetLayout> descriptor_list = {
      {ubo_descriptor_set_layout,
       descriptor_pools_[pipeline_info.pipeline_layout_type]
           ->DescriptorSetLayout()}};

  vk::PipelineLayoutCreateInfo pipeline_layout_info{
      {},
      static_cast<uint32_t>(descriptor_list.size()),
      descriptor_list.data(),
      1,
      &pcr};
  pipeline_info.layout = device_.createPipelineLayout(pipeline_layout_info);

  std::array<vk::PipelineShaderStageCreateInfo, 2>
      pipeline_shader_stage_create_infos = {
          vk::PipelineShaderStageCreateInfo(
              vk::PipelineShaderStageCreateFlags(),
              vk::ShaderStageFlagBits::eVertex,
              pipeline_info.vertex_shader->module(), "main"),
          vk::PipelineShaderStageCreateInfo(
              vk::PipelineShaderStageCreateFlags(),
              vk::ShaderStageFlagBits::eFragment,
              pipeline_info.fragment_shader->module(), "main")};

  vk::GraphicsPipelineCreateInfo graphics_pipeline_create_info{
      vk::PipelineCreateFlagBits::eAllowDerivatives,
      pipeline_shader_stage_create_infos,
      &vertex_input_state,
      &input_assembly,
      {},
      &viewport_state,
      &rasterizer,
      &multisampling,
      &depth_stencil_create_info,
      &color_blending,
      {},
      pipeline_info.layout,
      views_[0].render_pass->Get(),
      0

  };

  vk::Pipeline graphics_pipeline;
  vk::Result result;
  std::tie(result, graphics_pipeline) =
      device_.createGraphicsPipeline(nullptr, graphics_pipeline_create_info);
  if (result != vk::Result::eSuccess) {
    ALOGE("Failed to create graphics pipeline");
  }
  pipeline_info.pipeline = graphics_pipeline;
  return pipeline_info;
}

bool XrMLSceneGraphGraphicsDeviceVulkan::StartOfRenderLoop() {
  if (!IXrMLGraphicsDevice::StartOfRenderLoop()) {
    return false;
  }
  // Setup the UBO.
  ubo_buffer_ = std::make_unique<ml::Vulkan::UBO>(device_, allocator_);

  auto &ubo = ubo_buffer_->Get();

  {
    ml::Vulkan::LightSource *light = &ubo.light_sources[0];
    light->color = (XrColor4f{1.0f, 1.0f, 1.0f, 1.0f});
    light->pos = (XrVector4f{-2.0f, 2.0f, 0.0f, 0.0f});
    light->flags = ml::Vulkan::LightSource::ENABLED;
  }

  {
    ml::Vulkan::LightSource *light = &ubo.light_sources[1];
    light->color = (XrColor4f{1.0f, 1.0f, 1.0f, 1.0f});
    light->pos = (XrVector4f{-0.0f, 2.0f, 2.0f, 0.0f});
    light->flags = ml::Vulkan::LightSource::ENABLED;
  }

  {
    ml::Vulkan::LightSource *light = &ubo.light_sources[2];
    light->color = (XrColor4f{0.0f, 0.0f, 1.0f, 1.0f});
    light->pos = (XrVector4f{-1.5f, 2.0f, 2.0f, 0.0f});
    light->flags = 0;  // ml::Vulkan::LightSource::ENABLED;
  }

  {
    ml::Vulkan::LightSource *light = &ubo.light_sources[3];
    light->color = (XrColor4f{1.0f, 0.0f, 0.0f, 1.0f});
    light->pos = (XrVector4f{-0.5f, 2.0f, 2.0f, 0.0f});
    light->flags = 0;  // ml::Vulkan::LightSource::ENABLED;
  }

  ubo_buffer_->Sync();

  // Setup the desriptor pools for the different pipeline layouts.
  descriptor_pools_.emplace(Vulkan::TextureDescriptorPool::PBR,
                            std::make_unique<Vulkan::TextureDescriptorPool>(
                                device_, Vulkan::TextureDescriptorPool::PBR));
  descriptor_pools_.emplace(Vulkan::TextureDescriptorPool::UNLIT,
                            std::make_unique<Vulkan::TextureDescriptorPool>(
                                device_, Vulkan::TextureDescriptorPool::UNLIT));
  descriptor_pools_.emplace(
      Vulkan::TextureDescriptorPool::NATIVE_BUFFER,
      std::make_unique<Vulkan::TextureDescriptorPool>(
          device_, Vulkan::TextureDescriptorPool::NATIVE_BUFFER));

  // create the pipelines.
  // We have 5 pipelines using 3 different layouts.
  pipelines_[ml::Components::Mesh::TRIANGLE] =
      CreatePipeline(ml::Components::Mesh::TRIANGLE);
  pipelines_[ml::Components::Mesh::TRIANGLE_WIREFRAME] =
      CreatePipeline(ml::Components::Mesh::TRIANGLE_WIREFRAME);
  pipelines_[ml::Components::Mesh::LINES] =
      CreatePipeline(ml::Components::Mesh::LINES);
  pipelines_[ml::Components::Mesh::LINE_STRIP] =
      CreatePipeline(ml::Components::Mesh::LINE_STRIP);
  pipelines_[ml::Components::Mesh::PBR] =
      CreatePipeline(ml::Components::Mesh::PBR);
  pipelines_[ml::Components::Mesh::NATIVE_BUFFER] =
      CreatePipeline(ml::Components::Mesh::NATIVE_BUFFER);

  // create a single gui buffer.
  Vulkan::VulkanImGui::GuiCreateInfo create_info{
      core_,
      instance_,
      physical_device_,
      device_,
      command_buffers_[0],
      queue_,
      2000,
      500,
      allocator_,
      descriptor_pools_[Vulkan::TextureDescriptorPool::UNLIT]
          ->DescriptorSetLayout()};
  gui_ = std::make_unique<Vulkan::VulkanImGui>(create_info);

  UpdateObjects();

  return true;
}

ml::Vulkan::ImageBufferPtr
XrMLSceneGraphGraphicsDeviceVulkan::CheckAndCreateTexture(
    Scene::Node *node, Components::Material::TextureType texture_type,
    Components::ITexturePtr &texture, const Components::Mesh &mesh) {
  if (!texture) {
    return nullptr;
  }

  // see if we have a Vulkan Image ready to go.
  auto image_texture =
      texture->GetSharedComponent<ml::Vulkan::ImageBuffer>(texture_type);
  if (!image_texture) {
    // don't have it yet, create it!
    switch (texture->Type()) {
      case Components::ITexture::TextureType::STATIC: {
        if (texture->Open()) {
          image_texture = std::make_shared<ml::Vulkan::ImageBuffer>(
              core_, physical_device_, device_, allocator_);

          const vk::Format format =
              (texture_type == Components::Material::COLOR ||
               texture_type == Components::Material::EMISSIVE)
                  ? vk::Format::eR8G8B8A8Srgb
                  : vk::Format::eR8G8B8A8Unorm;

          if (texture->Encoding() == Components::ITexture::ENCODED) {
            image_texture->CreateTextureImage(command_buffers_[0], queue_,
                                              texture->Data(), texture->Size(),
                                              format, texture->Shader());
          } else {
            image_texture->CreateTextureImage(
                command_buffers_[0], queue_, texture->Data(), texture->Width(),
                texture->Height(), format, texture->Shader());
          }

          texture->Close();
        }
        break;
      }

      case Components::ITexture::TextureType::NATIVE_SURFACE: {
#ifdef XR_USE_PLATFORM_ANDROID
        auto native_img_texture =
            std::make_shared<ml::Vulkan::NativeImageBuffer>(
                core_, physical_device_, device_, allocator_);
        native_img_texture->TieWithTexture(texture);
        image_texture = native_img_texture;
#endif
        break;
      }
    }
  }

  if (image_texture) {
    texture->AddComponent(image_texture, texture_type);
  }
  return image_texture;
}

void XrMLSceneGraphGraphicsDeviceVulkan::UpdateObjects() {
  // if the scene graph changed, let's make sure we have all the buffers and
  // textures.
  scene_has_lights_ = false;

  native_texture_materials_.clear();

  root_node_->VisitNodes(
      false,
      [this](Scene::Node *node, const XrMatrix4x4f &node_T_world) -> bool {
        auto light = node->GetComponent<Components::Light>();
        if (light) {
          scene_has_lights_ = true;
        }
        // Vertex Buffer
        auto mesh = node->GetComponent<Components::Mesh>();
        if (!mesh || mesh->vertices.empty()) {
          return true;
        }

        // if vertex was not yet added, add it now!
        if (!node->GetComponent<Vulkan::Buffer>(Vulkan::Buffer::Type::VERTEX)) {
          auto vertices = mesh->vertices;

          auto vertex_buffer = std::make_shared<ml::Vulkan::Buffer>(
              allocator_,
              vk::BufferUsageFlagBits::eVertexBuffer |
                  vk::BufferUsageFlagBits::eTransferDst,
              VMA_ALLOCATION_CREATE_STRATEGY_MIN_OFFSET_BIT);

          vertex_buffer->CopyViaStaging(command_buffers_[0], queue_,
                                        vertices.size() * sizeof(vertices[0]),
                                        (const char *)vertices.data());
          node->AddComponent(vertex_buffer, Vulkan::Buffer::Type::VERTEX);
        }

        // Index Buffer
        if (!node->GetComponent<Vulkan::Buffer>(Vulkan::Buffer::Type::INDEX)) {
          auto index_buffer = std::make_shared<ml::Vulkan::Buffer>(
              allocator_,
              vk::BufferUsageFlagBits::eIndexBuffer |
                  vk::BufferUsageFlagBits::eTransferDst,
              VMA_ALLOCATION_CREATE_STRATEGY_MIN_OFFSET_BIT);

          const std::vector<uint16_t> &elements = mesh->indices;
          index_buffer->CopyViaStaging(
              command_buffers_[0], queue_,
              elements.size() *
                  sizeof(elements[0]),  // safe even if length = 0.
              (const char *)elements.data());
          node->AddComponent(index_buffer, Vulkan::Buffer::Type::INDEX);
        }

        if (!node->GetComponent<ml::Vulkan::MaterialDescriptorSet>()) {
          auto *descriptor_pool =
              descriptor_pools_[pipelines_[mesh->type].pipeline_layout_type]
                  .get();
          auto material_descriptor =
              std::make_shared<ml::Vulkan::MaterialDescriptorSet>(
                  descriptor_pool, pipelines_[mesh->type].default_textures);

          material_descriptor->StartSetup();

          auto gui = node->GetComponent<ml::Components::Gui>();
          if (gui) {
            // attach the gui
            auto image = gui_->ImageBuffer();
            material_descriptor->AddImage(
                Components::Material::TextureType::COLOR, image);

          } else {
            auto image = CheckAndCreateTexture(
                node, Components::Material::TextureType::COLOR,
                mesh->material->color_texture, *mesh);
            material_descriptor->AddImage(
                Components::Material::TextureType::COLOR, image);

            image = CheckAndCreateTexture(
                node, Components::Material::TextureType::METALLIC_ROUGHNESS,
                mesh->material->metallic_roughness_texture, *mesh);
            material_descriptor->AddImage(
                Components::Material::TextureType::METALLIC_ROUGHNESS, image);

            image = CheckAndCreateTexture(
                node, Components::Material::TextureType::NORMAL,
                mesh->material->normal_texture, *mesh);
            material_descriptor->AddImage(
                Components::Material::TextureType::NORMAL, image);

            image = CheckAndCreateTexture(
                node, Components::Material::TextureType::AO,
                mesh->material->occlusion_texture, *mesh);
            material_descriptor->AddImage(Components::Material::TextureType::AO,
                                          image);

            image = CheckAndCreateTexture(
                node, Components::Material::TextureType::EMISSIVE,
                mesh->material->emissive_texture, *mesh);
            material_descriptor->AddImage(
                Components::Material::TextureType::EMISSIVE, image);
          }
          if (material_descriptor->IsNative()) {
            native_texture_materials_.push_back(material_descriptor);
          }
          if (material_descriptor->HasImages()) {
            material_descriptor->FinishSetup(device_);
            node->AddComponent(material_descriptor);
          } else {
            node->AddComponent(pipelines_[mesh->type].default_descriptor_set);
          }
        }

        return true;
      });
}

ml::Vulkan::ImageBufferPtr
XrMLSceneGraphGraphicsDeviceVulkan::CreateDefaultTexture(
    ml::Components::Material::TextureType texture_type,
    ml::Vulkan::TextureDescriptorPool::PipelineLayoutType
        pipeline_layout_type) {
  std::vector<Vulkan::ImageBufferPtr> images;

  ml::Vulkan::ImageBufferPtr texture;
#ifdef XR_USE_PLATFORM_ANDROID
  if (pipeline_layout_type == Vulkan::TextureDescriptorPool::NATIVE_BUFFER) {
    texture = std::make_shared<ml::Vulkan::NativeImageBuffer>(
        core_, physical_device_, device_, allocator_);
  } else
#endif
  {
    texture = std::make_shared<ml::Vulkan::ImageBuffer>(core_, physical_device_,
                                                        device_, allocator_);
  }
  ml::Components::TextureData default_texture_image(
      ml::Resources::TEXTURE_DEFAULT);

  vk::Format format = texture_type == Components::Material::COLOR
                          ? vk::Format::eR8G8B8A8Srgb
                          : vk::Format::eR8G8B8A8Unorm;

  texture->CreateTextureImage(
      command_buffers_[0], queue_, default_texture_image.Data(),
      default_texture_image.Size(), format, ITexture::ShaderSettings{});

  return texture;
}

IGuiBackend *XrMLSceneGraphGraphicsDeviceVulkan::GetGui() {
  return gui_.get();
}
