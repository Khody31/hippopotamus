#include "keyboard_interface.h"

KeyboardInterface& KeyboardInterface::Get() {
  static KeyboardInterface instance;
  return instance;
}
bool KeyboardInterface::IsPressed(Qt::Key key) {
  return Get().key_states_[key];
}
bool KeyboardInterface::IsReleased(Qt::Key key) {
  return !Get().IsPressed(key);
}
void KeyboardInterface::OnPress(Qt::Key key) {
  Get().key_states_[key] = true;
}
void KeyboardInterface::OnRelease(Qt::Key key) {
  Get().key_states_[key] = false;
}
