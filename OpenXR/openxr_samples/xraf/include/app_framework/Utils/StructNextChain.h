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

#include <openxr/openxr.h>

#include <algorithm>
#include <vector>

namespace ml {

/*! \brief Helper class for managing next chains in OXR structures. */
class StructNextChain {
 public:
  /*! \brief Add structure to the chain.
   *
   * @param struct_ptr pointer to the structure
   *
   * Note: There is no deduplication mechanism.
   **/
  void AddStructure(XrBaseInStructure* struct_ptr);

  /*! \brief Removes first occurence of the structure from the chain.
   *
   * @param struct_ptr pointer to the structure
   *
   * Note: If given structure was not in the chain, nothing happens.
   **/
  void RemoveStructure(XrBaseInStructure* struct_ptr);

  /*! \brief Returns ptr that should be assigned to the _next_ member of the
   *parent structure. Will return nullptr when the chain is empty.
   **/
  void* GetChainRoot() const;

 private:
  std::vector<XrBaseInStructure*> structs_;
  void* chain_root_;

  void RebuildChain();
};

}  // namespace ml