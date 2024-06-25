#pragma once

#include <cstdint>

#include "type_id.h"

namespace ignosi::ecs {

class IComponent {
 public:
  virtual ~IComponent() = default;
  virtual std::uint32_t TypeID() const = 0;
};

template <typename T>
class Component : public IComponent {
 public:
  ~Component() override = default;

  Component(T&& data) : Data(std::forward<T>(data)) {}
  Component(const T& data) : Data(data) {}

  std::uint32_t TypeID() const { return TypeIDValue; }

  static constexpr std::uint32_t TypeIDValue =
      ecs::TypeID<IComponent>::template Value<T>();

  T Data;
};

}  // namespace ignosi::ecs
