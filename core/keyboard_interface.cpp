#include "keyboard_interface.h"

bool KeyboardInterface::IsKeyPressed(KeyAction bind) const {
  if (is_key_pressed_.find(bindings_.at(bind)) == is_key_pressed_.end()) {
    return false;
  }
  return is_key_pressed_.at(bindings_.at(bind));
}

void KeyboardInterface::OnPress(Qt::Key key) {
  is_key_pressed_[key] = true;
}

void KeyboardInterface::OnRelease(Qt::Key key) {
  is_key_pressed_[key] = false;
}

KeyboardInterface::KeyboardInterface() {
  bindings_ = {
      {KeyAction::kMoveRight, Qt::Key_D},
      {KeyAction::kMoveLeft, Qt::Key_A},
      {KeyAction::kMoveUp, Qt::Key_W},
      {KeyAction::kMoveDown, Qt::Key_S}
  };
}
