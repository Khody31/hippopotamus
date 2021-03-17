#pragma once

#include "Engine/Misc/vector_2d.h"

#include <vector>

class CoordinatesBase {
 public:
  void SetX(double x);
  void SetY(double y);
  void SetCoordinates(Vector2D coordinates);
  void MoveBy(Vector2D coordinates);

  [[nodiscard]] Vector2D GetCoordinates() const;

 protected:
  Vector2D coordinates_;
};
