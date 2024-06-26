#pragma once

#include <cstdint>

#include "type_id.h"

namespace ignosi::ecs {
class World;

class IComponent {
 public:
  virtual ~IComponent() = default;
  virtual std::uint32_t EntityID() const = 0;
  virtual std::uint32_t TypeID() const = 0;
};

template <typename T>
class Component : public IComponent {
  friend World;

  std::uint32_t m_EntityID;

  Component(std::uint32_t entityID, T&& data)
      : m_EntityID(entityID), Data(std::forward<T>(data)) {}

  Component(std::uint32_t entityID, const T& data)
      : m_EntityID(entityID), Data(data) {}

 public:
  ~Component() override = default;

  std::uint32_t TypeID() const override { return TypeIDValue; }
  std::uint32_t EntityID() const override { return m_EntityID; }

  static constexpr std::uint32_t TypeIDValue =
      ecs::TypeID<IComponent>::template Value<T>();

  T Data;
};

}  // namespace ignosi::ecs
