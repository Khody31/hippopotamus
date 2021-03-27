#pragma once

#include <QVector2D>

class TransformationComponentInterface {
 public:
  virtual void Update() = 0;

  void SetX(float x) {
    coordinates_.setX(x);
  }
  void SetY(float y) {
    coordinates_.setY(y);
  }
  void SetCoordinates(const QVector2D& coordinates) {
    coordinates_ = coordinates;
  }
  void SetVelocity(const QVector2D& velocity) {
    velocity_ = velocity;
  }
  [[nodiscard]] const QVector2D& GetCoordinates() const {
    return coordinates_;
  }
  void MoveBy(const QVector2D& shift) {
    coordinates_ += shift;
  }

 protected:
  QVector2D coordinates_{0,0};
  QVector2D velocity_{0,0};
};

