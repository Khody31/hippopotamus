#include "entity_manager.h"

#include <cassert>

EntityManager::EntityManager() : living_entity_count_(0) {
  for (Entity entity = 0; entity < constants::kMaxEntities; ++entity) {
    available_entities_.push_back(entity);
  }
}

Entity EntityManager::CreateEntity() {
  assert(living_entity_count_ < constants::kMaxEntities &&
      "Too many entities in existence.");

  Entity id = available_entities_.front();
  available_entities_.pop_front();
  ++living_entity_count_;
  return id;
}

void EntityManager::DestroyEntity(Entity entity) {
  assert(entity < constants::kMaxEntities && "entity out of range.");

  signatures_[entity].reset();
  available_entities_.push_back(entity);
  --living_entity_count_;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
  assert(entity < constants::kMaxEntities && "entity out of range.");
  signatures_[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
  assert(entity < constants::kMaxEntities && "entity out of range.");
  return signatures_[entity];
}
