#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include "entity.h"

namespace ignosi::ecs {
class World {
  std::vector<Entity> m_Entities;

 public:
  void Process(double delta);

  Entity CreateEntity();
};
}  // namespace ignosi::ecs
