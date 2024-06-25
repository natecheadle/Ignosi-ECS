#include "entity.h"

namespace ignosi::ecs {

Entity::Entity(World* pWorld, std::uint32_t id) : m_pWorld(pWorld), m_ID(id) {}

void Entity::RegisterComponent(const IComponent& component) {
  m_Components[component.TypeID()] = true;
}

void Entity::RemoveComponent(const IComponent& component) {
  m_Components[component.TypeID()] = false;
}
}  // namespace ignosi::ecs
