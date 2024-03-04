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

#include "../../include/app_framework/Utils/StructNextChain.h"

namespace ml {

void StructNextChain::AddStructure(XrBaseInStructure* struct_ptr) {
  if (struct_ptr) {
    structs_.push_back(struct_ptr);
    RebuildChain();
  }
}

void StructNextChain::RemoveStructure(XrBaseInStructure* struct_ptr) {
  if (struct_ptr) {
    const auto it = std::find(structs_.begin(), structs_.end(), struct_ptr);
    if (it != structs_.end()) {
      structs_.erase(it);
      RebuildChain();
    }
  }
}

void* StructNextChain::GetChainRoot() const {
  return chain_root_;
}

void StructNextChain::RebuildChain() {
  if (structs_.empty()) {
    chain_root_ = nullptr;
    return;
  }
  chain_root_ = structs_.front();
  for (size_t i = 1; i < structs_.size(); i++) {
    structs_[i - 1]->next = structs_[i];
  }
  structs_.back()->next = nullptr;
}

}  // namespace ml