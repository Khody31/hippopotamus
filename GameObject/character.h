#pragma once

#include "moving_object.h"

class Character : public MovingObject {
 public:
  void OnHit();

  void Shoot();

 protected:
  double health_max_;
  double health_cur_;
  double protection_;
};

