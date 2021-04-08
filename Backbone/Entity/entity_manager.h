#pragma ones

#include <cassert>
#include <bitset>
#include <array>
#include <queue>

#include "Backbone/constants.h"

using Entity = uint8_t;
using ComponentType = uint8_t;
using Signature = std::bitset<constants::MAX_COMPONENTS>;

class EntityManager
{
 public:
  EntityManager();

  Entity CreateEntity();
  void DestroyEntity(Entity entity);

  void SetSignature(Entity entity, Signature signature);
  Signature GetSignature(Entity entity);

 private:
  // unused entity IDs
  std::queue<Entity> mAvailableEntities{};

  // index == entity ID
  std::array<Signature, constants::MAX_ENTITIES> mSignatures{};

  // number of existing entities
  uint32_t mLivingEntityCount{};
};
