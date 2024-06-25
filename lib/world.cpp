#include "world.h"

#include <algorithm>

#include "entity.h"

namespace ignosi::ecs {

void World::Process(double delta) {}

Entity World::CreateEntity() {
  Entity newEntity(this, m_NextID++);
  m_Entities.push_back(newEntity);
  std::sort(
      m_Entities.begin(), m_Entities.end(),
      [](const Entity& lhs, const Entity& rhs) { return lhs.ID() < rhs.ID(); });
  return newEntity;
}
}  // namespace ignosi::ecs
