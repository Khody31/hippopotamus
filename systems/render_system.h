#pragma once

#include "engine/coordinator.h"
#include "components/components.h"
#include <unordered_set>

class GameScene;

class RenderSystem : public System {
 public:
  void Update(GameScene* scene);

  const std::unordered_set<Entity>& GetEntities();
};
