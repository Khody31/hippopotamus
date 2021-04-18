#pragma once

#include <unordered_map>
#include <Qt>

enum class KeyAction {
  kMoveUp,
  kMoveDown,
  kMoveLeft,
  kMoveRight
};

class KeyboardInterface {
 public:
  KeyboardInterface();

  void OnPress(Qt::Key);
  void OnRelease(Qt::Key);

  bool IsKeyPressed(KeyAction bind) const;

 private:
  std::unordered_map<Qt::Key, bool> is_key_pressed_;
  std::unordered_map<KeyAction, Qt::Key> bindings_;
};
