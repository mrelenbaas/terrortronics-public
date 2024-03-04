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

#include "../include/app_framework/vulkan/Buffer.h"

#ifdef XR_USE_GRAPHICS_API_VULKAN

#include "../include/app_framework/Logging.h"

using namespace ml::Vulkan;

Buffer::Buffer(VmaAllocator allocator, vk::BufferUsageFlags flags,
               VmaAllocationCreateFlags vma_flags)
    : allocator_(allocator),
      flags_(flags),
      vma_flags_(vma_flags),
      allocation_(VK_NULL_HANDLE),
      size_(0) {
}
Buffer::~Buffer() {
  if (allocation_ != VK_NULL_HANDLE) {
    vmaDestroyBuffer(allocator_, buffer_, allocation_);
  }
}
void Buffer::Set(const char *data, size_t size) {
  if (!buffer_) {
    throw std::runtime_error("Not yet allocated");
  }
  if (size > size_) {
    throw std::runtime_error("Too large");
  }
  if (data != nullptr) {
    void *mapped_data;
    vmaMapMemory(allocator_, allocation_, &mapped_data);
    memcpy(mapped_data, data, size);
    vmaUnmapMemory(allocator_, allocation_);
  }
}

void Buffer::Alloc(size_t size) {
  if (buffer_) {
    throw std::runtime_error("Already allocated");
  }
  size_ = size;
  auto buffer_info = vk::BufferCreateInfo{{}, size, flags_};

  VmaAllocationCreateInfo alloc_info = {};
  alloc_info.flags =
      vma_flags_;  // VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;
  alloc_info.usage = VMA_MEMORY_USAGE_AUTO;

  if (vmaCreateBuffer(allocator_, (VkBufferCreateInfo *)&buffer_info,
                      &alloc_info, (VkBuffer *)&buffer_, &allocation_,
                      nullptr) != VK_SUCCESS) {
    throw std::runtime_error("Error creating buffer");
  }
}
bool Buffer::Transfer(ml::Vulkan::CommandBuffer &command_buffer,
                      vk::Queue &queue, Buffer &source) {
  if (size_ == 0) {
    Alloc(source.size_);
  }

  if (source.size_ != size_) {
    throw std::runtime_error("Size mismatch");
  }

  vk::BufferCopy copyRegion{0, 0, size_};

  vk::CommandBuffer cb = command_buffer;
  command_buffer.wait();
  command_buffer.reset();
  command_buffer.begin(vk::CommandBufferBeginInfo{
      vk::CommandBufferUsageFlagBits::eOneTimeSubmit});
  cb.copyBuffer(*source.GetBuffer(), buffer_, 1, &copyRegion);
  command_buffer.end();
  vk::SubmitInfo submitInfo{};
  submitInfo.setCommandBufferCount(1);
  submitInfo.setCommandBuffers(cb);
  auto r = queue.submit(1, &submitInfo, command_buffer);
  if (r != vk::Result::eSuccess) {
    ALOGE("Unable to transfer buffer");
  }
  queue.waitIdle();
  return true;
}
#endif
