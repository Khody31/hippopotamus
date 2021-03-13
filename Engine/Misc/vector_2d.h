#pragma once

struct Vector2D {
  Vector2D& operator+=(const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  Vector2D operator+(const Vector2D& rhs) const {
    Vector2D result{*this};
    return result += rhs;
  }

  Vector2D operator-() const {
    return Vector2D{-x, -y};
  }
  Vector2D operator-=(const Vector2D& rhs) {
    return *this += -rhs;
  }
  Vector2D operator-(const Vector2D& rhs) const {
    return *this + -rhs;
  }
  Vector2D operator/(double num) const {
    return Vector2D{x / num, y / num};
  }
  Vector2D operator*(double num) const {
    return Vector2D{x * num, y * num};
  }

  double x;
  double y;
};
