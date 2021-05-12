#pragma once

#include <utility>
#include <unordered_set>

#include "components/components.h"
#include "engine/coordinator.h"
#include "core/keyboard_interface.h"

class Connector;

class CollisionSystem : public System {
 public:
  CollisionSystem(Connector* connector,
                  Coordinator* coordinator,
                  KeyboardInterface* keyboard);
  void Update();

  const std::unordered_set<Entity>& GetEntities();

 private:
  void UpdateCollisionComponents();
  void UpdateOtherComponents();

  Coordinator* coordinator_;
  KeyboardInterface* keyboard_;
  Connector* connector_;
};
