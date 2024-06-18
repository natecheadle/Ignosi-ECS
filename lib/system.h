#pragma once

#include <bitset>
#include <cstdint>

#include "entity.h"

namespace ignosi::ecs {
class World;

class System {
  World* m_pWorld;

  std::uint32_t m_ID;

 public:
  void Process(double delta);

  virtual const std::bitset<64>& ComponentFilter() const = 0;
};
}  // namespace ignosi::ecs
