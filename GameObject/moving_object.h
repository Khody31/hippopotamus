#pragma once

#include "game_object.h"
#include "vector2d.h"

class MovingObject : public GameObject {
 public:
  virtual void OnTick() = 0;
 protected:
  Vector2D velocity_;
};
