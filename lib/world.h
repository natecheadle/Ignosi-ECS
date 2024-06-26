#pragma once

#include <ignosi/dll_allocate.h>

#include <algorithm>
#include <cstdint>
#include <ignosi/dll_object_pool.hpp>
#include <ignosi/dll_unique_ptr.hpp>
#include <memory>
#include <vector>

#include "component.h"
#include "ecs_pointer.h"
#include "entity.h"
#include "query.h"
#include "system.h"

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
    memory::DllUniquePtr<Component<T>> Create(const Entity& entity, T&& obj) {
      return m_Pool.Create(Component<T>(entity.ID(), std::forward<T>(obj)));
    }

    memory::DllUniquePtr<Component<T>> Create(const Entity& entity,
                                              const T& obj) {
      return m_Pool.Create(Component<T>(entity.ID(), obj));
    }
  };

  std::vector<Entity> m_Entities;
  std::vector<std::unique_ptr<Query>> m_Queries;
  std::vector<std::unique_ptr<System>> m_Systems;
  std::atomic<std::uint32_t> m_NextID;

  std::unordered_map<std::uint32_t, std::unique_ptr<PoolContainer>> m_Pools;
  std::unordered_map<std::uint32_t,
                     std::array<memory::DllUniquePtr<IComponent>, 64>>
      m_EntityComponents;

  std::vector<IComponent*> m_ComponentToFree;
  std::vector<Entity> m_EntityToFree;
  std::vector<System*> m_SystemsToFree;
  std::vector<Query*> m_QueriesToFree;

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

  ECSPointer<System> RegisterSystem(std::unique_ptr<System> system);
  ECSPointer<Query> RegisterQuery(std::unique_ptr<Query> query);

  template <typename T>
  ECSPointer<Component<T>> CreateComponent(Entity& entity) {
    ComponentPoolContainer<T>* pPool =
        ((ComponentPoolContainer<T>*)m_Pools[Component<T>::TypeIDValue].get());
    memory::DllUniquePtr<Component<T>> newComponent =
        pPool->Create(entity, T());

    Component<T>* pNew = newComponent.get();
    entity.RegisterComponent(*pNew);

    m_EntityComponents[entity.ID()][Component<T>::TypeIDValue] =
        std::move(newComponent);

    return ECSPointer<Component<T>>(
        pNew, [this](Component<T>* pObj) { queueFree(pObj); });
  }

 private:
  void queueFree(IComponent* toFree);
  void queueFree(const Entity& toFree);
  void queueFree(Query* toFree);
  void queueFree(System* toFree);
};
}  // namespace ignosi::ecs
