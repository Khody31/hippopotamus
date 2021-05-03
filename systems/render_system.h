#pragma once

#include <set>

#include "engine/coordinator.h"
#include "components/components.h"

class GameScene;

class RenderSystem : public System {
 public:
  void Update(GameScene* scene);

  const std::set<Entity>& GetEntities();
};
