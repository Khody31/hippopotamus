#include <Engine/Core/keyboard_interface.h>
#include "transformation_component_player.h"
#include <cmath>

void TransformationComponentPlayer::Update() {
  Vector2D shift{0,0};
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveUp)) {
    shift += Vector2D{0, -0.07};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveDown)) {
    shift += Vector2D{0, 0.07};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveRight)) {
    shift += Vector2D{0.07, 0};
  }
  if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveLeft)) {
    shift += Vector2D{-0.07, 0};
  }
  shift.MakeLength(0.07);
  MoveBy(shift);
}
