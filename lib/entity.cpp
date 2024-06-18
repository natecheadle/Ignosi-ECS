#include "entity.h"

namespace ignosi::ecs {

void Entity::RegisterComponent(const IComponent& component) {
  m_Components[component.TypeID()] = true;
}

void Entity::RemoveComponent(const IComponent& component) {
  m_Components[component.TypeID()] = false;
}
}  // namespace ignosi::ecs
