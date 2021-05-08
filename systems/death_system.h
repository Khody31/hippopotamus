#pragma once

#include "engine/system.h"

class GameScene;

class DeathSystem : public System {
 public:
  void Update(Coordinator* coordinator, GameScene* scene);

  void SetPlayer(Entity player);

 public:
  Entity player_;
};
