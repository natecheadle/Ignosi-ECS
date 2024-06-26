#pragma once

#include <functional>
#include <vector>

#include "entity.h"

namespace ignosi::ecs {

class Query {
  std::vector<Entity> m_Result;
  std::function<bool(const Entity&)> m_Query;

 public:
  Query(std::function<bool(const Entity&)> query);
  void Run(const std::vector<Entity>& allEntities);
};
}  // namespace ignosi::ecs
