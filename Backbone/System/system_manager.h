#pragma once

#include <bitset>
#include <unordered_map>
#include <memory>
#include <cassert>

#include "Backbone/constants.h"
#include "game_system.h"

using Entity = uint8_t;
using ComponentType = uint8_t;
using Signature = std::bitset<constants::MAX_COMPONENTS>;

class SystemManager
{
 public:
  template<typename T>
  std::shared_ptr<T> RegisterSystem();
  template<typename T>
  void SetSignature(Signature signature);

  void EntityDestroyed(Entity entity);
  void EntitySignatureChanged(Entity entity, Signature entitySignature);

 private:
  // component type name -> signature
  std::unordered_map<const char*, Signature> mSignatures{};

  // component type name -> system pointer
  std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem() {
  const char* typeName = typeid(T).name();
  assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

  auto system = std::make_shared<T>();
  mSystems.insert({typeName, system});
  return system;
}

template<typename T>
void SystemManager::SetSignature(Signature signature) {
  const char* typeName = typeid(T).name();
  assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");
  mSignatures.insert({typeName, signature});
}
