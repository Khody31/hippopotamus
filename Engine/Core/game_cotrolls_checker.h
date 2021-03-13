#pragma once

#include "Engine/Misc/singleton.h"

enum class Control {
  kMoveUp,
  kMoveLeft,
  kMoveDown,
  kMoveRight,
  kShoot,
  kAction
};

class GameControlsChecker : public Singleton {
 public:
  void SetKeyPressed(int key);
  void SetKeyPressed(Control key);
  void SetKeyReleased(int key);
  void SetKeyReleased(Control key);

  bool IsKeyPressed(Control key);
 private:
  GameControlsChecker();

  std::map<int, Control> key_to_control_;
  std::map<Control, bool> is_control_pressed_;
};
