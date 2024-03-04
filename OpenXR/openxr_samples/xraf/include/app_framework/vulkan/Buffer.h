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

#include "../Components/Component.h"
#include "../OpenXRCommon.h"
#include "CommandBuffers.h"

namespace ml {
namespace Vulkan {
class Buffer : public ml::Components::IComponent {
 public:
  enum Type { UNKNOWN, VERTEX, INDEX, COLOR_TEXTURE, TEXTURE_COORDINATES };

  Buffer(VmaAllocator allocator, vk::BufferUsageFlags flags,
         VmaAllocationCreateFlags vma_flags);
  ~Buffer();

  Buffer(const Buffer &) = delete;
  Buffer &operator=(const Buffer &) = delete;
  Buffer(Buffer &&source) {
    allocator_ = source.allocator_;
    flags_ = source.flags_;
    vma_flags_ = source.vma_flags_;
    allocation_ = source.allocation_;
    source.allocation_ = VK_NULL_HANDLE;
    buffer_ = source.buffer_;
    source.buffer_ = VK_NULL_HANDLE;
    size_ = source.size_;
  }
  Buffer &operator=(Buffer &&source) {
    if (this != &source) {
      allocator_ = source.allocator_;
      flags_ = source.flags_;
      vma_flags_ = source.vma_flags_;
      allocation_ = source.allocation_;
      source.allocation_ = VK_NULL_HANDLE;
      buffer_ = source.buffer_;
      source.buffer_ = VK_NULL_HANDLE;
      size_ = source.size_;
    }
    return *this;
  }

  void Set(const char *data, size_t size);
  void Alloc(size_t size);

  inline vk::Buffer *GetBuffer() {
    return &buffer_;
  }

  bool Transfer(ml::Vulkan::CommandBuffer &command_buffer, vk::Queue &queue,
                Buffer &source);

  bool CopyViaStaging(ml::Vulkan::CommandBuffer &command_buffer,
                      vk::Queue &queue, size_t size, const char *data) {
    ml::Vulkan::Buffer staging_buffer{
        allocator_, vk::BufferUsageFlagBits::eTransferSrc,
        VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT};
    staging_buffer.Alloc(size);
    staging_buffer.Set(data, size);
    Transfer(command_buffer, queue, staging_buffer);
    return true;
  }

 protected:
  VmaAllocator allocator_;
  vk::BufferUsageFlags flags_;
  VmaAllocationCreateFlags vma_flags_;
  VmaAllocation allocation_;
  vk::Buffer buffer_;
  size_t size_;
};
}  // namespace Vulkan
}  // namespace ml
