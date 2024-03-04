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

#include <stdexcept>

#include "../include/app_framework/AssetManager.h"
#include "../include/app_framework/Utils/AndroidHelper.h"

using namespace ml;

// https://developer.android.com/ndk/reference/group/asset#group___asset_1ga0037ce3c10a591fe632f34c1aa62955c
class AndroidAsset : public IAsset {
 public:
  explicit AndroidAsset(AAsset *asset) : asset_(asset) {
  }
  ~AndroidAsset() override {
    Close();
  }

  void Close() override {
    if (asset_ != nullptr) {
      AAsset_close(asset_);
      asset_ = nullptr;
    }
  }
  size_t Read(void *buffer, size_t count) override {
    if (!asset_) {
      throw std::runtime_error("asset closed before calling Read");
    }
    return AAsset_read(asset_, buffer, count);
  }

  int64_t Seek(int64_t offset, int whence) override {
    if (!asset_) {
      throw std::runtime_error("asset closed before calling Seek");
    }
    return AAsset_seek64(asset_, offset, whence);
  }

  int64_t Length() override {
    if (!asset_) {
      throw std::runtime_error("asset closed before calling Length");
    }
    return AAsset_getLength64(asset_);
  }

  const void *GetBuffer() override {
    if (!asset_) {
      throw std::runtime_error("asset closed before calling GetBuffer");
    }
    return AAsset_getBuffer(asset_);
  }

  int OpenFileDescriptor(int64_t &start, int64_t &length) override {
    if (!asset_) {
      throw std::runtime_error(
          "asset closed before calling OpenFileDescriptor");
    }
    return AAsset_openFileDescriptor64(asset_, &start, &length);
  }

 private:
  AAsset *asset_;
};

class AndroidAssetManager : public IAssetManager {
  AAssetManager *asset_manager_;

 public:
  explicit AndroidAssetManager(ANativeActivity *activity)
      : asset_manager_(activity->assetManager) {
  }

  IAssetPtr Open(const char *filename) override {
    AAsset *asset = AAssetManager_open(asset_manager_, filename, 0);
    if (asset == nullptr) {
      return nullptr;
    }

    return std::make_shared<AndroidAsset>(asset);
  }
};

IAssetManagerPtr IAssetManager::Factory(struct android_app *app) {
  return std::make_shared<AndroidAssetManager>(app->activity);
}
