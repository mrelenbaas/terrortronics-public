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

#include <algorithm>
#include <cstdio>
#include <cstring>

#ifdef _WIN32
#include <vector>  // Needed to compile mio on Win32: https://github.com/mandreyel/mio/issues/76
#define NOMINMAX
#endif
#include <mio/mio.hpp>
#include <stdexcept>
#include <system_error>

#include "../include/app_framework/AssetManager.h"
#include "../include/app_framework/Logging.h"

// #ifdef CXX17
#include <cstddef>
using mmap_source = mio::basic_mmap_source<std::byte>;
// #endif

using namespace ml;

// https://developer.android.com/ndk/reference/group/asset#group___asset_1ga0037ce3c10a591fe632f34c1aa62955c
class HostAsset : public IAsset {
 public:
  HostAsset(mmap_source mio) : mio_(std::move(mio)), read_pos_(0) {
  }

  virtual void Close() {
    mio_.unmap();
  }

  virtual size_t Read(void *buffer, size_t count) {
    if (!mio_.is_open()) {
      throw std::runtime_error("asset closed before calling Read");
    }
    size_t to_read = std::min(count, mio_.size() - read_pos_);
    memcpy(buffer, &mio_[read_pos_], to_read);
    read_pos_ += to_read;
    return to_read;
  }

  virtual int64_t Seek(int64_t offset, int whence) {
    if (!mio_.is_open()) {
      throw std::runtime_error("asset closed before calling Seek");
    }
    switch (whence) {
      case SEEK_SET:
        read_pos_ = offset;
        break;
      case SEEK_CUR:
        read_pos_ += offset;
        break;
      case SEEK_END:
        read_pos_ = mio_.size() + offset - 1;
        break;
    }
    read_pos_ = std::clamp(read_pos_, (int64_t)0, (int64_t)(mio_.size()) - 1);
    return read_pos_;
  }

  virtual int64_t Length() {
    if (!mio_.is_open()) {
      throw std::runtime_error("asset closed before calling Length");
    }
    return mio_.size();
  }

  virtual const void *GetBuffer() {
    if (!mio_.is_open()) {
      throw std::runtime_error("asset closed before calling GetBuffer");
    }
    return &mio_[0];
  }

  virtual int OpenFileDescriptor(int64_t &start, int64_t &length) {
    if (!mio_.is_open()) {
      throw std::runtime_error("asset closed before calling Length");
    }
#ifdef _WIN32
    throw std::runtime_error("Not supported on Windows.");
#else
    return mio_.file_handle();
#endif
  }

 private:
  std::string filename_;
  mmap_source mio_;
  int64_t read_pos_;
};

class HostAssetManager : public IAssetManager {
 public:
  HostAssetManager() = default;

  virtual IAssetPtr Open(const char *filename) {
    std::error_code error;
    mmap_source mio;
    mio.map(filename, error);
    if (error) {
      return nullptr;
    }
    return std::make_shared<HostAsset>(std::move(mio));
  }
};

IAssetManagerPtr IAssetManager::Factory(struct android_app *app) {
  return std::make_shared<HostAssetManager>();
}
