#pragma once

#include "engine/coordinator.h"
#include "engine/system.h"

/* This system stores entities which should be deleted when changing a room.
 * For example, bullets.
*/
class GarbageSystem : public System {
 public:
  explicit GarbageSystem(Coordinator* coordinator);
  void Update();

 private:
  Coordinator* coordinator_;
};
