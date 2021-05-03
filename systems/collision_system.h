#pragma once

#include "engine/coordinator.h"

class CollisionSystem : public System {
 public:
  void Update(Coordinator* coordinator);

 private:
  void UpdateCollisionComponents(Coordinator* coordinator);
  void UpdateOtherComponents(Coordinator* coordinator);
};
