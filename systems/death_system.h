#pragma once

#include "engine/coordinator.h"
#include "core/scene.h"

class DeathSystem : public System {
 public:
  explicit DeathSystem(Coordinator* coordinator,
                       Connector* connector,
                       Entity* player);

  void Update();

 private:
  Entity* player_;
  Coordinator* coordinator_;
  Connector* connector_;
  int bosses_alive_ = 2;
};
