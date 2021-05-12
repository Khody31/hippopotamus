#pragma once

#include "engine/system.h"

class Scene;

class DeathSystem : public System {
 public:
  explicit DeathSystem(Coordinator* coordinator, Scene* scene);

  void Update();

  void SetPlayer(Entity player);

 public:
  Entity player_;
  Coordinator* coordinator_;
  Scene* scene_;
};
