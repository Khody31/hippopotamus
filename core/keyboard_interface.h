#pragma once

#include <unordered_map>
#include <Qt>

class KeyboardInterface {
 public:
  KeyboardInterface();

  enum class Bind {
    kMoveUp,
    kMoveDown,
    kMoveLeft,
    kMoveRight
  };

  void OnPress(Qt::Key);
  void OnRelease(Qt::Key);

  bool IsKeyPressed(Bind bind) const;

 private:
  std::unordered_map<Qt::Key, bool> is_key_pressed_;
  std::unordered_map<Bind, Qt::Key> bindings_;
};
