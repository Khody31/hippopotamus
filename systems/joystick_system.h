#pragma once

#include "engine/system.h"
#include "core/keyboard_interface.h"

class JoystickSystem : public System {
 public:
  JoystickSystem();
  void Update(Coordinator* coordinator);
  void SetKeyboardInterface(const KeyboardInterface*);

 private:
  const KeyboardInterface* keyboard_interface_;
};
