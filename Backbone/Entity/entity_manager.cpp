#include "entity_manager.h"


EntityManager::EntityManager() {
  for (Entity entity = 0; entity < constants::MAX_ENTITIES; ++entity) {
    mAvailableEntities.push(entity);
  }
}

Entity EntityManager::CreateEntity() {
  assert(mLivingEntityCount < constants::MAX_ENTITIES && "Too many entities in existence.");

  Entity id = mAvailableEntities.front();
  mAvailableEntities.pop();
  ++mLivingEntityCount;

  return id;
}

void EntityManager::DestroyEntity(Entity entity) {
  assert(entity < constants::MAX_ENTITIES && "Entity out of range.");

  mSignatures[entity].reset();
  mAvailableEntities.push(entity);
  --mLivingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
  assert(entity < constants::MAX_ENTITIES && "Entity out of range.");
  mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
  assert(entity < constants::MAX_ENTITIES && "Entity out of range.");

  return mSignatures[entity];
}


