#pragma once

#include "engine/coordinator.h"
#include "core/keyboard_interface.h"

class CollisionSystem : public System {
 public:
  CollisionSystem();
  void Update(Coordinator* coordinator);
  void SetKeyboardInterface(const KeyboardInterface*);

 private:
  const KeyboardInterface* keyboard_;

  void UpdateCollisionComponents(Coordinator* coordinator);
  void UpdateOtherComponents(Coordinator* coordinator);
  void ResolveRoomChangingCollision();
};
