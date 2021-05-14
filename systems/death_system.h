#pragma once

#include "engine/system.h"

class Scene;

class DeathSystem : public System {
 public:
  explicit DeathSystem(Coordinator* coordinator, Scene* scene, Entity* entity);

  void Update();
 public:
  Coordinator* coordinator_;
  Scene* scene_;
  Entity* player_;
};
