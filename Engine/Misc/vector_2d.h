#pragma once

struct Vector2D {
  Vector2D& operator+=(const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  double x;
  double y;
};
