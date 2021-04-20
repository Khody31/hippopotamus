#include "joystick_system.h"
#include "engine/coordinator.h"
#include "components/components.h"

JoystickSystem::JoystickSystem() : keyboard_(nullptr) {}

void JoystickSystem::SetKeyboardInterface(const KeyboardInterface* ptr) {
  keyboard_ = ptr;
}

void JoystickSystem::Update(Coordinator* coordinator) {
  assert(keyboard_ && "JoystickSystem: No keyboard interface");
  for (const auto& entity : entities_) {
    auto& motion_comp = coordinator->GetComponent<MotionComponent>(entity);
    QVector2D direction;
    if (keyboard_->IsKeyPressed(KeyAction::kMoveDown)) {
      direction += {0.0, -1.0};
    }
    if (keyboard_->IsKeyPressed(KeyAction::kMoveUp)) {
      direction += {0.0, 1.0};
    }
    if (keyboard_->IsKeyPressed(KeyAction::kMoveLeft)) {
      direction += {-1.0, 0.0};
    }
    if (keyboard_->IsKeyPressed(KeyAction::kMoveRight)) {
      direction += {1.0, 0.0};
    }
    motion_comp.direction = direction.normalized();
    motion_comp.speed = 1;
  }
}
