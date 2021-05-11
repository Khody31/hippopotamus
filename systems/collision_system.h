#pragma once

#include <components/components.h>
#include "engine/coordinator.h"
#include "core/keyboard_interface.h"

class Connector;

class CollisionSystem : public System {
 public:
  CollisionSystem();
  void Update(Coordinator* coordinator);
  void SetKeyboardInterface(const KeyboardInterface*);
  void SetConnector(Connector*);

  const std::unordered_set<Entity>& GetEntities();

 private:
  const KeyboardInterface* keyboard_;
  Connector* connector_;

  void UpdateCollisionComponents(Coordinator* coordinator);
  void UpdateOtherComponents(Coordinator* coordinator);
  bool IsCollisionNeeded();
};
