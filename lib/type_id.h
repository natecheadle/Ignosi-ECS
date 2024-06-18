#pragma once
#include <cstdint>
#include <typeindex>
#include <unordered_map>
namespace ignosi::ecs {
template <typename T>
class TypeID {
  static std::uint32_t m_NextID;
  static std::unordered_map<std::type_index, std::uint32_t> s_TypeIDLookup;

 public:
  template <typename U>
  static std::uint32_t Value() {
    std::type_index index(typeof(U));
    auto it = s_TypeIDLookup.find(index);
    if (it == s_TypeIDLookup.end()) {
      std::uint32_t newID = m_NextID++;
      s_TypeIDLookup.insert({index, newID});
    }
    return it->second;
  }
};

}  // namespace ignosi::ecs
