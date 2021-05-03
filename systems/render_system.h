#pragma once

#include "engine/coordinator.h"
#include "components/components.h"
#include <set>

class GameScene;

class RenderSystem : public System {
 public:
  void Update(GameScene* scene);

  const std::set<Entity>& GetEntities();
};
