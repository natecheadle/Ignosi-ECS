#include "world.h"

#include <algorithm>
#include <cstdlib>
#include <memory>

#include "component.h"
#include "ecs_pointer.h"
#include "entity.h"
#include "query.h"

namespace ignosi::ecs {

void World::Process(double delta) {
  for (const auto& query : m_Queries) {
    query->Run(m_Entities);
  }

  for (const auto& system : m_Systems) {
    system->Process(delta);
  }

  for (const auto& system : m_SystemsToFree) {
    auto it = std::find_if(m_Systems.begin(), m_Systems.end(),
                           [system](const std::unique_ptr<System>& sys) {
                             return sys.get() == system;
                           });
    m_Systems.erase(it);
  }

  for (const auto& query : m_QueriesToFree) {
    auto it = std::find_if(
        m_Queries.begin(), m_Queries.end(),
        [query](const std::unique_ptr<Query>& q) { return q.get() == query; });
    m_Queries.erase(it);
  }

  for (const auto& component : m_ComponentToFree) {
    m_EntityComponents[component->EntityID()][component->TypeID()].reset();
  }
  m_ComponentToFree.clear();

  for (const Entity& entity : m_EntityToFree) {
    m_EntityComponents.erase(m_EntityComponents.find(entity.ID()));
    m_Entities.erase(
        std::lower_bound(m_Entities.begin(), m_Entities.end(), entity));
  }
  m_EntityToFree.clear();
}

ECSPointer<Query> World::RegisterQuery(std::unique_ptr<Query> query) {
  Query* pNew = query.get();
  m_Queries.push_back(std::move(query));
  return ECSPointer<Query>(pNew, [this](Query* pObj) { queueFree(pObj); });
}

ECSPointer<System> World::RegisterSystem(std::unique_ptr<System> system) {
  System* pNew = system.get();
  m_Systems.push_back(std::move(system));
  std::sort(m_Systems.begin(), m_Systems.end(),
            [](const std::unique_ptr<System>& lhs,
               const std::unique_ptr<System>& rhs) {
              return lhs->Priority() < rhs->Priority();
            });
  return ECSPointer<System>(pNew, [this](System* pObj) { queueFree(pObj); });
}

Entity World::CreateEntity() {
  Entity newEntity(m_NextID++);
  m_Entities.push_back(newEntity);
  std::sort(m_Entities.begin(), m_Entities.end());
  return newEntity;
}

void World::queueFree(IComponent* pToFree) {
  m_ComponentToFree.push_back(pToFree);
}

void World::queueFree(const Entity& toFree) {
  m_EntityToFree.push_back(toFree);
}

void World::queueFree(Query* toFree) { m_QueriesToFree.push_back(toFree); }

void World::queueFree(System* toFree) { m_SystemsToFree.push_back(toFree); }
}  // namespace ignosi::ecs
