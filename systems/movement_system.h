#pragma once

#include "engine/system.h"

class MovementSystem : public System {
 public:
  void Update(Coordinator* coordinator);
};
