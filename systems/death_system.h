#pragma once

#include "core/spawner.h"
#include "core/random_generator.h"
#include "engine/coordinator.h"
#include "core/scene.h"

class DeathSystem : public System {
 public:
  explicit DeathSystem(Coordinator* coordinator,
                       Connector* connector,
                       Entity* player,
                       Scene* scene,
                       Spawner* spawner);

  void Update();

 private:
  Entity* player_;
  Scene* scene_;
  Coordinator* coordinator_;
  Connector* connector_;
  Spawner* spawner_;

  RandomGenerator random_generator_;

  int bosses_alive_ = 1;
};
