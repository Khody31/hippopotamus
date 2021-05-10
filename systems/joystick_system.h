#pragma once

#include "engine/system.h"
#include "core/keyboard_interface.h"

class JoystickSystem : public System {
 public:
  JoystickSystem(Coordinator* coordinator, KeyboardInterface* keyboard);
  void Update();

 private:
  Coordinator* coordinator_;
  KeyboardInterface* keyboard_;
};
