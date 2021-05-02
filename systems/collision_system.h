#pragma once

#include "engine/coordinator.h"
#include "core/keyboard_interface.h"

class Connector;

class CollisionSystem : public System {
 public:
  CollisionSystem();
  void Update(Coordinator* coordinator);
  void SetKeyboardInterface(const KeyboardInterface*);
  void SetConnector(Connector*);

 private:
  const KeyboardInterface* keyboard_;
  Connector* connector_;

  void UpdateCollisionComponents(Coordinator* coordinator);
  void UpdateOtherComponents(Coordinator* coordinator);
  void ResolveRoomChangingCollision(int id);
};
