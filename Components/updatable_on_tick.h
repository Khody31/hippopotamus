#pragma once

#include "Core/game_timer.h"

class UpdatableOnTick : private UpdatableOnTickInterface {
 public:
  UpdatableOnTick() {
    GameTimer::GetInstance().StartTracking(this);
  }
  ~UpdatableOnTick() {
    GameTimer::GetInstance().StopTracking(this);
  }
};
