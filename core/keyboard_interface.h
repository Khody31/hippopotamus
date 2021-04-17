#pragma once

#include <unordered_map>
#include <Qt>

class KeyboardInterface {
 public:
  void OnPress(Qt::Key);
  void OnRelease(Qt::Key);

  bool IsKeyPressed(Qt::Key key) const;

 private:
  std::unordered_map<Qt::Key, bool> is_key_pressed_;
};
