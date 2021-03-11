#pragma once

#include "game_object.h"

struct Vector {
  double x = 0;
  double y = 0;
};

class MovingObject : public GameObject {
 public:
  virtual void OnTick() = 0;

 protected:
  Vector velocity_;
};
