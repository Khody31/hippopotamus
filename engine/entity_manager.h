#pragma once

#include <cassert>
#include <array>
#include <list>

#include "engine/constants.h"
#include "types.h"

class EntityManager {
 public:
  EntityManager();

  Entity CreateEntity();
  void DestroyEntity(Entity entity);

  void SetSignature(Entity entity, const Signature& signature);
  Signature GetSignature(Entity entity);

 private:
  // unused entity IDs
  std::list<Entity> available_entities_{};

  // index == entity ID
  std::array<Signature, constants::kMaxEntities> signatures_{};

  // number of existing entities
  uint32_t living_entity_count_;
};
