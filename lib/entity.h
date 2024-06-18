#pragma once

#include <bitset>
#include <cstdint>

#include "component.h"

namespace ignosi::ecs {

class World;

class Entity {
  World* m_pWorld;

  std::bitset<64> m_Components;
  std::uint32_t m_ID;

 public:
  std::uint32_t ID() const;

  void RegisterComponent(const IComponent& component);
  void RemoveComponent(const IComponent& component);
};
}  // namespace ignosi::ecs
