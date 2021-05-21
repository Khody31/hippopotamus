#pragma once

#include <array>
#include <list>

#include "constants.h"
#include "types.h"

class EntityManager {
 public:
  EntityManager();

  Entity CreateEntity();
  void DestroyEntity(Entity entity);

  void SetSignature(Entity entity, Signature signature);
  Signature GetSignature(Entity entity);

 private:
  // unused entity IDs
  std::list<Entity> available_entities_;

  // index == entity ID
  std::array<Signature, constants::kMaxEntities> signatures_{};

  // number of existing entities
  uint32_t living_entity_count_;
};
