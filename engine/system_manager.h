#pragma once

#include <unordered_map>
#include <memory>
#include <cassert>
#include <typeindex>

#include "engine/constants.h"
#include "game_system.h"
#include "types.h"

class SystemManager {
 public:
  template<typename T>
  std::shared_ptr<T> RegisterSystem();
  template<typename T>
  void SetSignature(const Signature& signature);

  void EntityDestroyed(Entity entity);
  void EntitySignatureChanged(Entity entity, Signature entity_signature);

 private:
  // component type name -> signature
  std::unordered_map<std::type_index, Signature> signatures_{};

  // component type name -> system pointer
  std::unordered_map<std::type_index, std::shared_ptr<System>> systems_{};
};

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem() {
  auto index = std::type_index(typeid(T));
  assert(systems_.find(index) == systems_.end()
             && "Registering system more than once.");

  auto system = std::make_shared<T>();
  systems_.insert({index, system});
  return system;
}

template<typename T>
void SystemManager::SetSignature(const Signature& signature) {
  auto index = std::type_index(typeid(T));
  assert(systems_.find(index) != systems_.end() &&
      "system used before registered.");
  signatures_.insert({index, signature});
}
