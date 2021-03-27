#pragma once

#include "Engine/Misc/vector_2d.h"

class TransformationComponentInterface {
 public:
  virtual void Update() = 0;

  void SetX(double x) {
    coordinates_.x = x;
  }
  void SetY(double y) {
    coordinates_.y = y;
  }
  void SetCoordinates(const Vector2D& coordinates) {
    coordinates_ = coordinates;
  }
  void SetVelocity(const Vector2D& velocity) {
    velocity_ = velocity;
  }
  [[nodiscard]] Vector2D GetCoordinates() const {
    return coordinates_;
  }
  void MoveBy(Vector2D shift) {
    coordinates_ += shift;
  }

 protected:
  Vector2D coordinates_{0,0};
  Vector2D velocity_{0,0};
};

