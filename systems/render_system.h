#pragma once

#include <unordered_set>

#include "engine/coordinator.h"
#include "components/components.h"

class GameScene;

class GameScene;

class RenderSystem : public System {
 public:
  void Update(GameScene* scene);

  const std::unordered_set<Entity>& GetEntities();
};
