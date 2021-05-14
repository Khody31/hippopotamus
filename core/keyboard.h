#pragma once

#include <unordered_map>

#include <QInternal>

enum class KeyAction {
  kMoveUp,
  kMoveDown,
  kMoveLeft,
  kMoveRight,
  kAction
};

class Keyboard {
 public:
  Keyboard();

  void OnPress(Qt::Key);
  void OnRelease(Qt::Key);

  bool IsKeyPressed(KeyAction bind) const;

 private:
  std::unordered_map<Qt::Key, bool> is_key_pressed_;
  std::unordered_map<KeyAction, Qt::Key> bindings_;
};
