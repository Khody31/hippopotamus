#include "system_manager.h"

void SystemManager::EntityDestroyed(Entity entity) {
  // no check because of the set
  for (auto const &pair : mSystems) {
    auto const &system = pair.second;
    system->mEntities.erase(entity);
  }
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature
entitySignature) {
  for (auto const &pair : mSystems) {
    auto const &type = pair.first;
    auto const &system = pair.second;
    auto const &systemSignature = mSignatures[type];

    if ((entitySignature & systemSignature) == systemSignature) {
      // match - insert into set
      system->mEntities.insert(entity);
    } else {
      // no match - erase from set
      system->mEntities.erase(entity);
    }
  }
}