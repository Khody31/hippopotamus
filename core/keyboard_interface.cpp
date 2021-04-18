#include "keyboard_interface.h"

bool KeyboardInterface::IsKeyPressed(Bind bind) const {
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
      {Bind::kMoveRight, Qt::Key_D},
      {Bind::kMoveLeft, Qt::Key_A},
      {Bind::kMoveUp, Qt::Key_W},
      {Bind::kMoveDown, Qt::Key_S}
  };
}
