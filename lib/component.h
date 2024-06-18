#pragma once

#include <cstdint>

#include "type_id.h"

namespace ignosi::ecs {

class IComponent {
 public:
  virtual std::uint32_t TypeID() const = 0;
};

template <typename T>
class Component : public IComponent {
 public:
  std::uint32_t TypeID() const {
    return ecs::TypeID<Component>::template Value<T>();
  }

  T Data;
};

}  // namespace ignosi::ecs
