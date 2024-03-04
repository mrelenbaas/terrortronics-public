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

#include "../../include/app_framework/vulkan/VulkanGui.h"

#include <backends/imgui_impl_vulkan.h>
#include <imgui.h>

using namespace ml::Vulkan;

VulkanImGui::VulkanImGui(const GuiCreateInfo &create_info)
    : create_info_(create_info) {
  // one time only.
  static bool context_created = false;
  if (!context_created) {
    ImGui::CreateContext();
    context_created = true;
    auto &io = ImGui::GetIO();
    io.DisplaySize.x = create_info.width;
    io.DisplaySize.y = create_info.height;
    io.BackendPlatformName = "vulkan-open-xr";
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.MouseDrawCursor = false;
    io.MousePos = ImVec2(10, 10);
  }

  // Overkill?
  const uint32_t descriptor_count = 100;
  std::array<vk::DescriptorPoolSize, 11> pool_sizes = {{
      {vk::DescriptorType::eSampler, descriptor_count},
      {vk::DescriptorType::eCombinedImageSampler, descriptor_count},
      {vk::DescriptorType::eSampledImage, descriptor_count},
      {vk::DescriptorType::eStorageImage, descriptor_count},
      {vk::DescriptorType::eUniformTexelBuffer, descriptor_count},
      {vk::DescriptorType::eStorageTexelBuffer, descriptor_count},
      {vk::DescriptorType::eUniformBuffer, descriptor_count},
      {vk::DescriptorType::eStorageBuffer, descriptor_count},
      {vk::DescriptorType::eUniformBufferDynamic, descriptor_count},
      {vk::DescriptorType::eStorageBufferDynamic, descriptor_count},
      {vk::DescriptorType::eInputAttachment, descriptor_count},
  }};

  vk::DescriptorPoolCreateInfo ci{
      {}, descriptor_count * pool_sizes.size(), pool_sizes};

  pool_ = create_info_.device.createDescriptorPool(ci);

  PrepareRenderPass();

  ImGui_ImplVulkan_InitInfo init_info{
      .Instance = create_info.instance,
      .PhysicalDevice = create_info_.physical_device,
      .Device = create_info_.device,
      .QueueFamily = 0,
      .Queue = create_info_.queue,
      .PipelineCache = {},
      .DescriptorPool = pool_,
      .Subpass = 0,
      .MinImageCount = 2,
      .ImageCount = 2,
      .MSAASamples = VK_SAMPLE_COUNT_1_BIT};

  ImGui_ImplVulkan_Init(&init_info, render_pass_->Get());
  create_info_.command_buffer.wait();
  create_info_.command_buffer.reset();
  create_info_.command_buffer.begin(vk::CommandBufferBeginInfo{
      vk::CommandBufferUsageFlagBits::eOneTimeSubmit});

  ImGui_ImplVulkan_CreateFontsTexture(create_info_.command_buffer);

  create_info_.command_buffer.end();
  vk::SubmitInfo submitInfo{};
  submitInfo.setCommandBufferCount(1);
  vk::CommandBuffer cb = create_info_.command_buffer;
  submitInfo.setCommandBuffers(cb);
  auto r =
      create_info_.queue.submit(1, &submitInfo, create_info_.command_buffer);
  if (r != vk::Result::eSuccess) {
    ALOGE("Unable to submit image");
  }
  create_info_.queue.waitIdle();
}

VulkanImGui::~VulkanImGui() {
  ImGui_ImplVulkan_DestroyFontUploadObjects();
  ImGui_ImplVulkan_Shutdown();
  create_info_.device.destroyDescriptorPool(pool_);
}

void VulkanImGui::PrepareRenderPass() {
  image_buffer_ = std::make_shared<Vulkan::ImageBuffer>(
      create_info_.core, create_info_.physical_device, create_info_.device,
      create_info_.allocator);

  image_buffer_->CreateTextureImage(
      create_info_.command_buffer, create_info_.queue, create_info_.width,
      create_info_.height,
      vk::ImageUsageFlagBits::eSampled |
          vk::ImageUsageFlagBits::eColorAttachment);

  std::vector<vk::AttachmentDescription> at;

  at.push_back(vk::AttachmentDescription(
      {}, image_buffer_->Format(), vk::SampleCountFlagBits::e1,
      vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore,
      vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare,
      vk::ImageLayout::eUndefined, vk::ImageLayout::eShaderReadOnlyOptimal));

  // Use subpass dependencies for layout transitions
  std::vector<vk::SubpassDependency> dependencies;

  dependencies.push_back({VK_SUBPASS_EXTERNAL, 0,
                          vk::PipelineStageFlagBits::eFragmentShader,
                          vk::PipelineStageFlagBits::eColorAttachmentOutput,
                          vk::AccessFlagBits::eShaderRead,
                          vk::AccessFlagBits::eColorAttachmentWrite,
                          vk::DependencyFlagBits::eByRegion});
  dependencies.push_back({0, VK_SUBPASS_EXTERNAL,
                          vk::PipelineStageFlagBits::eColorAttachmentOutput,
                          vk::PipelineStageFlagBits::eFragmentShader,
                          vk::AccessFlagBits::eColorAttachmentWrite,
                          vk::AccessFlagBits::eShaderRead,
                          vk::DependencyFlagBits::eByRegion});

  render_pass_ = std::make_unique<Vulkan::RenderPass>(
      create_info_.device, image_buffer_->Format(), vk::Format::eUndefined, at,
      dependencies);
  render_target_ = std::make_unique<Vulkan::RenderTarget>(create_info_.device);

  render_target_->Bind(image_buffer_, render_pass_.get());
  image_buffer_->OverrideImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal);
}

void VulkanImGui::Render(vk::CommandBuffer command_buffer, vk::Queue queue) {
  std::array<vk::ClearValue, 1> clearValues;

  clearValues[0].color.float32[0] = 0.0f;
  clearValues[0].color.float32[1] = 0.3f;  // TODO Green here to debug.
  clearValues[0].color.float32[2] = 0.0f;
  clearValues[0].color.float32[3] = 1.0f;  // TODO opaque to debug.

  ImDrawData *draw_data = ImGui::GetDrawData();

  vk::RenderPassBeginInfo info = {};

  info.renderPass = RenderPass()->Get();
  info.framebuffer = RenderTarget()->GetFrameBuffer();
  info.renderArea.extent.width = create_info_.width;
  info.renderArea.extent.height = create_info_.height;
  info.clearValueCount = 1;
  info.pClearValues = clearValues.data();
  command_buffer.beginRenderPass(info, vk::SubpassContents::eInline);
  ImGui_ImplVulkan_RenderDrawData(draw_data, command_buffer);
  command_buffer.endRenderPass();
}
