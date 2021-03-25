#include <Engine/Core/keyboard_interface.h>
#include "transformation_component_player.h"
#include <cmath>

void TransformationComponentPlayer::Update() {
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveUp)) {
    velocity_ += Vector2D{0, -0.07};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveDown)) {
    velocity_ += Vector2D{0, 0.07};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveRight)) {
    velocity_ += Vector2D{0.07, 0};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveLeft)) {
    velocity_ += Vector2D{-0.07, 0};
  }
  if (velocity_.x != 0 || velocity_.y != 0) {
    velocity_ *=
        0.07 / std::sqrt(velocity_.x * velocity_.x + velocity_.y * velocity_.y);
  }
  MoveBy(velocity_);
  velocity_ = {0,0};
}
