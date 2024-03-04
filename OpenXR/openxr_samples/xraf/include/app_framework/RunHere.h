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

#include <chrono>
#include <functional>
#include <future>
#include <optional>

namespace ml {

/*! \brief Utility class that allows running code async while collecting results
 * elsewhere.
 *
 * #include <app_framework/RunHere.h>
 *
 * class App {
 * public:
 *
 * void OnReady() {
 *   auto f = std::async([]() -> std::function<Scene::Node*()> {
 *
 *      Scene::Node * node;
 *      // this is slow, so do it on a separate thread.
 *      std::tie(std::ignore, node) =
 * Components::GLTF::Factory("PBR_Sphere2.glb");
 *
 *      return [node]() -> Scene::Node * {
 *        // this one just returns but it can do other things as well.
 *        return node;
 *      }
 *   });
 *   run_here_.Queue(std::move(f));
 *
 * }
 *
 * void OnUpdate() {
 *   if (auto node = run_here_.Process()) {
 *      // only gets here if not null.
 *      GetRoot()->AddChild(node);
 *   }
 * }
 *
 * protected:
 *   RunHere<Scene::Node*> run_here_;
 * }
 *
 * Note that "T" cannot be void.
 *
 * */
template <typename T>
class RunHere {
 public:
  /*! \brief Type of the future to return.
   *
   * The returned function will be run on the where Process is called from.
   *
   */
  using FutureFunction = std::future<std::function<T()>>;

  /*! \brief Queues up a future */
  void Queue(FutureFunction future) {
    future_functions_.push_back(std::move(future));
  }

  /*! \brief Checks any queued up futures to see if they are ready.
   *
   * If timeout is 0 it does not block. If timeout is larger than 0
   * it will wait for that duration on EACH of the futures that is pending.
   *
   * */
  std::optional<T> Process(
      std::chrono::milliseconds timeout = std::chrono::milliseconds(0)) {
    for (auto it = future_functions_.begin(); it != future_functions_.end();
         it++) {
      auto &future = *it;
      if (future.valid()) {
        if (future.wait_for(timeout) == std::future_status::ready) {
          auto keep = std::move(future);
          future_functions_.erase(it);
          return keep.get()();
        }
      }
    }
    return {};
  }

  /*! \brief Non blocking call returning true if any futures are outstanding. */
  bool AwaitingFutures() {
    return !future_functions_.empty();
  }

 protected:
  std::vector<FutureFunction> future_functions_;
};

}  // namespace ml