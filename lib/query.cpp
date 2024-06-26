#include "query.h"

#include "entity.h"

namespace ignosi::ecs {

Query::Query(std::function<bool(const Entity&)> query)
    : m_Query(std::move(query)) {}

void Query::Run(const std::vector<Entity>& allEntities) {
  m_Result.clear();
  m_Result.reserve(allEntities.size());

  for (const Entity& entity : allEntities) {
    if (m_Query(entity)) {
      m_Result.push_back(entity);
    }
  }
}
}  // namespace ignosi::ecs
