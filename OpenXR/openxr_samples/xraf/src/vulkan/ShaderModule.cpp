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

#include "../include/app_framework/vulkan/ShaderModule.h"

#include <exception>

#include "../include/app_framework/AssetManager.h"
#include "../include/app_framework/XrCore.h"

using namespace ml::Vulkan;

ShaderModule::ShaderModule(XrCore *core, vk::Device device,
                           const std::vector<uint8_t> &data)
    : device_(device) {
  vk::ShaderModuleCreateInfo createInfo{};
  createInfo.codeSize = data.size();
  createInfo.pCode = reinterpret_cast<const uint32_t *>(data.data());
  shader_module_ = device.createShaderModule(createInfo);
}

ShaderModule::ShaderModule(XrCore *core, vk::Device device,
                           ml::Resources::Resource shader)
    : device_(device) {
  const unsigned char *data;
  size_t size;
  if (!ml::Resources::Get(shader, data, size)) {
    throw std::runtime_error("unable to  load shader");
  }
  vk::ShaderModuleCreateInfo createInfo{};
  createInfo.codeSize = size;  // byte size.
  createInfo.pCode = reinterpret_cast<const uint32_t *>(data);
  shader_module_ = device.createShaderModule(createInfo);
}

ShaderModule::~ShaderModule() {
  device_.destroyShaderModule(shader_module_);
}
