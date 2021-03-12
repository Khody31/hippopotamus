#pragma once

#include "vector2d.h"
#include "moving_listener.h"

#include <vector>

class CoordinatesBase {
 public:
  void SetX(double x);
  void SetY(double y);
  void SetCoordinates(Vector2D coordinates);

  Vector2D GetCoordinates() const;
 private:
  void OnMove();

  Vector2D coordinates_;
  std::vector<MovingListener*> listeners_;
};
