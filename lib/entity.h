#pragma once

#include <bitset>
#include <cstdint>

#include "component.h"

namespace ignosi::ecs {

class World;

class Entity {
  friend World;

  std::bitset<64> m_Components;
  std::uint32_t m_ID;

  Entity(std::uint32_t id);

  void RegisterComponent(const IComponent& component);
  void RemoveComponent(const IComponent& component);

 public:
  std::uint32_t ID() const;

  const std::bitset<64>& RegisteredComponents() const;

  friend bool operator==(const Entity& lhs, const Entity& rhs);
  friend bool operator!=(const Entity& lhs, const Entity& rhs);
  friend bool operator<(const Entity& lhs, const Entity& rhs);
  friend bool operator<=(const Entity& lhs, const Entity& rhs);
  friend bool operator>(const Entity& lhs, const Entity& rhs);
  friend bool operator>=(const Entity& lhs, const Entity& rhs);
};
}  // namespace ignosi::ecs
