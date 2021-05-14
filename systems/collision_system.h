#pragma once

#include "core/keyboard.h"
#include "engine/coordinator.h"

class Connector;

class CollisionSystem : public System {
 public:
  CollisionSystem(Connector* connector,
                  Coordinator* coordinator,
                  Keyboard* keyboard);
  void Update();

 private:
  void UpdateCollisionComponents();
  void UpdateOtherComponents();

  Connector* connector_;
  Coordinator* coordinator_;
  Keyboard* keyboard_;
};
