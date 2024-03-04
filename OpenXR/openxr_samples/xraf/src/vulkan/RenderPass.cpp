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

#include "../include/app_framework/vulkan/RenderPass.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

using namespace ml::Vulkan;

RenderPass::RenderPass(vk::Device device, vk::Format image_format,
                       vk::Format depth_image_format)
    : device_(device),
      image_format_(image_format),
      depth_image_format_(depth_image_format) {
  std::vector<vk::AttachmentDescription> at;

  at.push_back(vk::AttachmentDescription(
      {}, image_format, vk::SampleCountFlagBits::e1,
      vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore,
      vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare,
      vk::ImageLayout::eColorAttachmentOptimal,
      vk::ImageLayout::eColorAttachmentOptimal));

  at.push_back(vk::AttachmentDescription(
      {}, depth_image_format, vk::SampleCountFlagBits::e1,
      vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eDontCare,
      vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare,
      vk::ImageLayout::eUndefined,
      vk::ImageLayout::eDepthStencilAttachmentOptimal));

  std::vector<vk::SubpassDependency> dependencies;
  dependencies.push_back(vk::SubpassDependency{
      0,
      0,
      vk::PipelineStageFlagBits::eColorAttachmentOutput |
          vk::PipelineStageFlagBits::eEarlyFragmentTests,
      vk::PipelineStageFlagBits::eColorAttachmentOutput |
          vk::PipelineStageFlagBits::eEarlyFragmentTests,
      {},
      vk::AccessFlagBits::eColorAttachmentWrite |
          vk::AccessFlagBits::eDepthStencilAttachmentWrite,
      vk::DependencyFlagBits::eByRegion});

  vk::AttachmentReference color_ref(0,
                                    vk::ImageLayout::eColorAttachmentOptimal);
  vk::AttachmentReference depth_ref(
      1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

  vk::SubpassDescription sub_pass({}, vk::PipelineBindPoint::eGraphics, 0,
                                  nullptr, 1, &color_ref, nullptr, &depth_ref);

  vk::RenderPassCreateInfo rp_info(
      {}, static_cast<uint32_t>(at.size()), at.data(), 1, &sub_pass,
      static_cast<uint32_t>(dependencies.size()), dependencies.data());

  render_pass_ = device_.createRenderPass(rp_info);
}

RenderPass::RenderPass(vk::Device device, vk::Format image_format,
                       vk::Format depth_image_format,
                       std::vector<vk::AttachmentDescription> attachments,
                       std::vector<vk::SubpassDependency> dependencies)
    : device_(device),
      image_format_(image_format),
      depth_image_format_(depth_image_format) {
  vk::AttachmentReference color_ref(0,
                                    vk::ImageLayout::eColorAttachmentOptimal);
  vk::AttachmentReference depth_ref(
      1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

  vk::SubpassDescription sub_pass(
      {}, vk::PipelineBindPoint::eGraphics, 0, nullptr, 1, &color_ref, nullptr,
      depth_image_format != vk::Format::eUndefined ? &depth_ref : nullptr);

  vk::RenderPassCreateInfo rp_info(
      {}, static_cast<uint32_t>(attachments.size()), attachments.data(), 1,
      &sub_pass, static_cast<uint32_t>(dependencies.size()),
      dependencies.data());

  render_pass_ = device_.createRenderPass(rp_info);
}

RenderPass::~RenderPass() {
  device_.destroy(render_pass_);
}

#endif