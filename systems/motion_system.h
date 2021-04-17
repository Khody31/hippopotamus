#pragma once

#include "engine/system.h"

class MotionSystem : public System {
 public:
  void Update(Coordinator* coordinator);
};
