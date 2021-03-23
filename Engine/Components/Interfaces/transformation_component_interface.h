#pragma once

class Vector2D;

class TransformationComponentInterface {
 public:
  virtual void Update() = 0;

  virtual void SetX(double x) = 0;
  virtual void SetY(double y) = 0;
  virtual void SetCoordinates(Vector2D coordinates) = 0;
  virtual void MoveBy(Vector2D coordinates) = 0;

  [[nodiscard]] virtual Vector2D GetCoordinates() const = 0;
};

