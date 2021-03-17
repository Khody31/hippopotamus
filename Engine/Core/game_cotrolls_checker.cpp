#include "game_cotrolls_checker.h"

GameControlsChecker::GameControlsChecker() {
  key_to_control_[Qt::Key_W] = Control::kMoveUp;
  key_to_control_[Qt::Key_Up] = Control::kMoveUp;
  key_to_control_[1062] = Control::kMoveUp;

  key_to_control_[Qt::Key_D] = Control::kMoveRight;
  key_to_control_[Qt::Key_Right] = Control::kMoveRight;
  key_to_control_[1042] = Control::kMoveRight;

  key_to_control_[Qt::Key_S] = Control::kMoveDown;
  key_to_control_[Qt::Key_Down] = Control::kMoveDown;
  key_to_control_[1067] = Control::kMoveDown;

  key_to_control_[Qt::Key_A] = Control::kMoveLeft;
  key_to_control_[Qt::Key_Left] = Control::kMoveLeft;
  key_to_control_[1060] = Control::kMoveLeft;

  key_to_control_[Qt::Key_F] = Control::kAction;
  key_to_control_[1040] = Control::kAction;

  key_to_control_[Qt::Key_Space] = Control::kShoot;
}

void GameControlsChecker::SetKeyPressed(int key) {
  SetKeyPressed(key_to_control_[key]);
}

void GameControlsChecker::SetKeyPressed(Control key) {
  is_control_pressed_[key] = true;
}

void GameControlsChecker::SetKeyReleased(int key) {
  SetKeyReleased(key_to_control_[key]);
}

void GameControlsChecker::SetKeyReleased(Control key) {
  is_control_pressed_[key] = false;
}

bool GameControlsChecker::IsKeyPressed(Control key) {
  return is_control_pressed_[key];
}

GameControlsChecker& GameControlsChecker::GetInstance() {
  static GameControlsChecker instance;
  return instance;
}
