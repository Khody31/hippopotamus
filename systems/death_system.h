#pragma once

#include "engine/system.h"

class GameScene;

class DeathSystem : public System {
 public:
  void Update(Coordinator* coordinator);

  void SetScene(GameScene* scene);
  void SetPlayer(Entity player);

 public:
  GameScene* scene_;
  Entity player_;
};
