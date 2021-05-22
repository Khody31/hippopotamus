#pragma once

#include "engine/coordinator.h"
#include "core/scene.h"

class DeathSystem : public System {
 public:
  explicit DeathSystem(Coordinator* coordinator, Scene* scene, Entity* entity);

  void Update();

 private:
  Entity* player_;
  Coordinator* coordinator_;
  Scene* scene_;

  int enemies_alive = 100;
};
