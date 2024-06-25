#pragma once

#include <ignosi/dll_allocate.h>

#include <algorithm>
#include <cstdint>
#include <ignosi/dll_object_pool.hpp>
#include <ignosi/dll_unique_ptr.hpp>
#include <vector>

#include "component.h"
#include "ecs_pointer.h"
#include "entity.h"

namespace ignosi::ecs {
class World {
  class PoolContainer {
   public:
    virtual int TypeID() const = 0;
  };

  template <typename T>
  class ComponentPoolContainer : public PoolContainer {
    memory::DllObjectPool<Component<T>> m_Pool;

   public:
    int TypeID() const { return Component<T>::TypeIDValue; }
    memory::DllUniquePtr<Component<T>> Create(T&& obj) {
      return m_Pool.Create(Component<T>(std::forward<T>(obj)));
    }

    memory::DllUniquePtr<Component<T>> Create(const T& obj) {
      return m_Pool.Create(Component<T>(obj));
    }
  };

  std::vector<Entity> m_Entities;
  std::vector<memory::DllUniquePtr<IComponent>> m_Components;
  std::atomic<std::uint32_t> m_NextID;

  std::unordered_map<std::uint32_t, std::unique_ptr<PoolContainer>> m_Pools;

  std::vector<IComponent*> m_ToFree;

 public:
  void Process(double delta);

  Entity CreateEntity();

  template <typename T>
  void RegisterComponent() {
    if (m_Pools.find(Component<T>::TypeIDValue) == m_Pools.end()) {
      m_Pools.insert({Component<T>::TypeIDValue,
                      std::make_unique<ComponentPoolContainer<T>>()});
    }
  }

  template <typename T>
  ECSPointer<Component<T>> CreateComponent() {
    ComponentPoolContainer<T>* pPool =
        ((ComponentPoolContainer<T>*)m_Pools[Component<T>::TypeIDValue].get());
    memory::DllUniquePtr<Component<T>> newComponent = pPool.Create(T());

    Component<T>* pNew = newComponent.get();

    m_Components.push_back(memory::CastDllUniquePtr<IComponent>(newComponent));
    std::sort(m_Components.begin(), m_Components.end());
    return ECSPointer<Component<T>>(
        pNew, [this](Component<T>* pObj) { queueFree(pObj); });
  }

 private:
  template <typename T>
  void queueFree(Component<T>* pToFree) {
    m_ToFree.push_back(pToFree);
  }
};
}  // namespace ignosi::ecs
