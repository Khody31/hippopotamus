#pragma once

#include <unordered_map>
#include <memory>
#include <cassert>

#include "engine/constants.h"
#include "game_system.h"
#include "types.h"


class SystemManager {
 public:
  template<typename T>
  std::shared_ptr<T> RegisterSystem();
  template<typename T>
  void SetSignature(Signature signature);

  void EntityDestroyed(Entity entity);
  void EntitySignatureChanged(Entity entity, Signature entity_signature);

 private:
  // component type name -> signature
  std::unordered_map<const char *, Signature> signatures_{};

  // component type name -> system pointer
  std::unordered_map<const char *, std::shared_ptr<System>> systems_{};
};

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem() {
  const char *type_name = typeid(T).name();
  assert(systems_.find(type_name) == systems_.end()
         && "Registering system more than once.");

  auto system = std::make_shared<T>();
  systems_.insert({type_name, system});
  return system;
}

template<typename T>
void SystemManager::SetSignature(Signature signature) {
  const char *type_name = typeid(T).name();
  assert(systems_.find(type_name) != systems_.end() &&
         "system used before registered.");
  signatures_.insert({type_name, signature});
}
