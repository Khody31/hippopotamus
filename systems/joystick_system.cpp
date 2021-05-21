#include "joystick_system.h"

#include "components/components.h"

JoystickSystem::JoystickSystem(Coordinator* coordinator,
                               Keyboard* keyboard) :
    coordinator_(coordinator), keyboard_(keyboard) {}

void JoystickSystem::Update() {
  if (keyboard_->IsBlocked()) {
    return;
  }
  for (const auto& entity : entities_) {
    auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
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
    motion.direction = direction.normalized();
    motion.current_speed = motion.initial_speed;
  }
}
