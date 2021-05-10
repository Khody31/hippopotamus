#pragma once

#include "engine/system.h"

class MovementSystem : public System {
 public:
  explicit MovementSystem(Coordinator* coordinator);
  void Update();

 private:
  Coordinator* coordinator_;
};
