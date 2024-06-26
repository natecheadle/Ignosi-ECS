#include "entity.h"

namespace ignosi::ecs {

Entity::Entity(std::uint32_t id) : m_ID(id) {}

void Entity::RegisterComponent(const IComponent& component) {
  m_Components[component.TypeID()] = true;
}

void Entity::RemoveComponent(const IComponent& component) {
  m_Components[component.TypeID()] = false;
}

const std::bitset<64>& Entity::RegisteredComponents() const {
  return m_Components;
}

bool operator==(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID == rhs.m_ID;
}

bool operator!=(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID != rhs.m_ID;
}

bool operator<(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID < rhs.m_ID;
}

bool operator<=(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID <= rhs.m_ID;
}

bool operator>(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID > rhs.m_ID;
}

bool operator>=(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID >= rhs.m_ID;
}
}  // namespace ignosi::ecs
