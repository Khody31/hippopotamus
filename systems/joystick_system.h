#pragma once

#include "engine/coordinator.h"
#include "core/keyboard.h"

class JoystickSystem : public System {
 public:
  JoystickSystem(Coordinator* coordinator, Keyboard* keyboard);
  void Update();

 private:
  Coordinator* coordinator_;
  Keyboard* keyboard_;
};
