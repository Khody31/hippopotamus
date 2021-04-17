#include "joystick_system.h"
#include "engine/coordinator.h"
#include "components/components.h"

void JoystickSystem::SetKeyboardInterface(const KeyboardInterface* ptr) {
  keyboard_interface_ = ptr;
}

JoystickSystem::JoystickSystem() : keyboard_interface_(nullptr) {}

void JoystickSystem::Update(Coordinator* coordinator) {
  assert(keyboard_interface_ && "JoystickSystem: No keyboard interface");
  for (const auto& entity : entities_) {
    auto& motion_comp = coordinator->GetComponent<MovementComponent>(entity);
    QVector2D direction;
    if (keyboard_interface_->IsKeyPressed(Qt::Key_S)) {
      direction += {0.0, -1.0};
    }
    if (keyboard_interface_->IsKeyPressed(Qt::Key_W)) {
      direction += {0.0, 1.0};
    }
    if (keyboard_interface_->IsKeyPressed(Qt::Key_A)) {
      direction += {-1.0, 0.0};
    }
    if (keyboard_interface_->IsKeyPressed(Qt::Key_D)) {
      direction += {1.0, 0.0};
    }
    motion_comp.direction = direction;
  }
}
