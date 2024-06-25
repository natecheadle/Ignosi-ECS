#pragma once

#include <ignosi/dll_allocate.h>

#include <cstdint>
#include <ignosi/dll_unique_ptr.hpp>
#include <vector>

#include "component.h"
#include "entity.h"

namespace ignosi::ecs {
class World {
  std::vector<Entity> m_Entities;
  std::vector<memory::DllUniquePtr<IComponent>> m_Components;
  std::atomic<std::uint32_t> m_NextID;

 public:
  void Process(double delta);

  Entity CreateEntity();
};
}  // namespace ignosi::ecs
