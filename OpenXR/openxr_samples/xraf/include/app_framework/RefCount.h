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

#include <atomic>
#include <cstdint>

namespace ml {

/*!\brief Reference counter base class
 *
 * A light weight fast access reference counted
 * base class.
 *
 * Upon creation of a new object make sure to call
 * Acquire() if the code owns the object.
 *
 */
class RefCount {
 public:
  RefCount() : count_(0) {
  }
  virtual ~RefCount() {
  }

  /*!\brief Increase the reference count */
  inline void Acquire() {
    count_++;
  }

  /*!\brief Decrease the reference count
   *
   * Code may NOT use the object after calling
   * Release as it might have been destroyed.
   */
  inline void Release() {
    uint32_t old_cnt = count_.fetch_sub(1);
    if (old_cnt == 1) {
      delete this;
    }
  }

 private:
  std::atomic<uint32_t> count_;
};

}  // namespace ml
