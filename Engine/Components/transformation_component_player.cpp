#include <Engine/Core/keyboard_interface.h>
#include "transformation_component_player.h"

void TransformationComponentPlayer::SetX(double x) {
  coordinates_.x = x;
}

void TransformationComponentPlayer::SetY(double y) {
  coordinates_.y = y;
}

void TransformationComponentPlayer::SetCoordinates(Vector2D coordinates) {
  coordinates_ = coordinates;
}

Vector2D TransformationComponentPlayer::GetCoordinates() const {
  return coordinates_;
}

void TransformationComponentPlayer::MoveBy(Vector2D coordinates) {
  coordinates_ += coordinates;
}

void TransformationComponentPlayer::Update() {
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveUp)) {
    MoveBy({0, -0.07});
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveDown)) {
    MoveBy({0, 0.07});
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveRight)) {
    MoveBy({0.07, 0});
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveLeft)) {
    MoveBy({-0.07, 0});
  }
}
