#pragma once

#include "engine/system.h"

class DeathSystem : public System {
 public:
  void Update(Coordinator* coordinator);
};