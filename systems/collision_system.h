#pragma once

#include <unordered_set>
#include <QSoundEffect>

#include "core/keyboard.h"
#include "engine/coordinator.h"

class Connector;

class CollisionSystem : public System {
 public:
  CollisionSystem(Connector* connector,
                  Coordinator* coordinator,
                  Keyboard* keyboard,
                  Entity* player);
  void Update();

  const std::unordered_set<Entity>& GetEntities();

 private:
  void UpdateCollisionComponents();
  void UpdateOtherComponents();

  Connector* connector_;
  Coordinator* coordinator_;
  Keyboard* keyboard_;
  Entity* player_;
};
