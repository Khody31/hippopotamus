#include <QVector2D>

#include "engine/core/keyboard_interface.h"
#include "transformation_component_player.h"

void TransformationComponentPlayer::Update() {
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveUp)) {
    velocity_ += QVector2D{0, -0.07};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveDown)) {
    velocity_ += QVector2D{0, 0.07};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveRight)) {
    velocity_ += QVector2D{0.07, 0};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveLeft)) {
    velocity_ += QVector2D{-0.07, 0};
  }
  if (velocity_.x() != 0 || velocity_.y() != 0) {
    velocity_.normalize();
    velocity_ *= 0.07;
  }
  MoveBy(velocity_);
  velocity_ = {0,0};
}
