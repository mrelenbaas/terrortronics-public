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

#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

namespace ml {

namespace Components {
class ComponentHolder;
class IComponent;
using IComponentPtr = std::shared_ptr<IComponent>;
/*! \brief Interface of any object that is going to be part of a ComponentHolder
 * collection.
 */
class IComponent {
 public:
  virtual ~IComponent() {
  }

  /*! \brief Returns true if component is shareable.
   * If this component can be shared without side effects (aka no state)
   * this function returns true. If it returns false a copy needs to be
   * made using DeepCopy before 'sharing' with another ComponentHolder.
   */
  virtual bool Shareable() const {
    return true;
  }

  /*! \brief returns a newly allocated copy.
   * If ::Shareable() returns false this must be implemented, if Shareable
   * returns false this must return nullptr.
   */
  virtual IComponentPtr DeepCopy(ComponentHolder *context) const {
    return nullptr;
  }
};

class ComponentHolder {
 public:
  virtual ~ComponentHolder() {
  }
  /*!\brief Adds a component
   *
   * If only one object of a type is going to be inserted the "id" parameter
   * may be ignored. If there are more of the same type, distinguish using
   * the id parameter.
   *
   * */
  template <typename T, typename U = T>
  void AddComponent(std::shared_ptr<T> &component, const uint32_t id = 0) {
    components_.emplace(std::make_pair(std::type_index(typeid(U)), id),
                        component);
  }

  /*!\brief Get a pointer to the component */
  template <typename T>
  T *GetComponent(const uint32_t id = 0) {
    auto it = components_.find(std::make_pair(std::type_index(typeid(T)), id));
    if (it == components_.end()) {
      return nullptr;
    }
    return reinterpret_cast<T *>(it->second.get());
  }
  /*!\brief Get a pointer to the component */
  template <typename T>
  std::shared_ptr<T> GetSharedComponent(const uint32_t id = 0) {
    auto it = components_.find(std::make_pair(std::type_index(typeid(T)), id));
    if (it == components_.end()) {
      return nullptr;
    }
    return std::static_pointer_cast<T>(it->second);
  }

  /*!\brief Removes a component */
  template <typename T>
  void RemoveComponent(const uint32_t id = 0) {
    auto it = components_.find(std::make_pair(std::type_index(typeid(T)), id));
    if (it != components_.end()) {
      components_.erase(it);
    }
  }

  /*!\brief Removes all components. */
  void ClearComponents() {
    components_.clear();
  }

  /*! \brief Copies references of components.
   *
   * By default components can be shared between component holders.
   * This allows sharing of textures and meshes between nodes and
   * avoids incurring the memory overhead of copies, including in
   * graphics memory.
   * Some components however should not be shared and are marked
   * by returning false from Component::Shareable(). For those
   * un-sharable components DeepCopy is called.
   */
  void ShareComponents(ComponentHolder *other, void *context) {
    components_ = other->components_;
    for (auto it : components_) {
      if (!it.second->Shareable()) {
        components_[it.first] = it.second->DeepCopy(this);
      }
    }
  }

 private:
  typedef std::pair<std::type_index, uint32_t> key_pair;

  struct key_pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const {
      return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
  };

  std::unordered_map<key_pair, IComponentPtr, key_pair_hash> components_;
};

}  // namespace Components

}  // namespace ml