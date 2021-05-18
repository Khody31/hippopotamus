#pragma once

#include <unordered_set>

#include "core/keyboard.h"
#include "engine/coordinator.h"

class Connector;

class CollisionSystem : public System {
 public:
  CollisionSystem(Connector* connector,
                  Coordinator* coordinator,
                  Keyboard* keyboard);
  void Update();

  const std::unordered_set<Entity>& GetEntities();

 private:
  void UpdateCollisionComponents();
  void UpdateOtherComponents();

  Connector* connector_;
  Coordinator* coordinator_;
  Keyboard* keyboard_;
};
