#include "keyboard_interface.h"

KeyboardInterface& KeyboardInterface::Get() {
  static KeyboardInterface instance;
  return instance;
}
bool KeyboardInterface::IsPressed(quint32 key_code) {
  return Get().key_states_[key_code];
}
bool KeyboardInterface::IsReleased(quint32 key_code) {
  return !Get().IsPressed(key_code);
}
void KeyboardInterface::OnPress(quint32 key_code) {
  Get().key_states_[key_code] = true;
}
void KeyboardInterface::OnRelease(quint32 key_code) {
  Get().key_states_[key_code] = false;
}
