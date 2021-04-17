#include "keyboard_interface.h"

bool KeyboardInterface::IsKeyPressed(Qt::Key key) const {
  if (is_key_pressed_.find(key) == is_key_pressed_.end()) {
    return false;
  }
  return is_key_pressed_.at(key);
}
void KeyboardInterface::OnPress(Qt::Key key) {
  is_key_pressed_[key] = true;
}
void KeyboardInterface::OnRelease(Qt::Key key) {
  is_key_pressed_[key] = false;
}
