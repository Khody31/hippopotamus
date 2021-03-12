#include "coordinates_base.h"

void CoordinatesBase::SetX(double x) {
  coordinates_.x = x;
}

void CoordinatesBase::SetY(double y) {
  coordinates_.y = y;
}

void CoordinatesBase::SetCoordinates(Vector2D coordinates) {
  coordinates_ = coordinates;
}

Vector2D CoordinatesBase::GetCoordinates() const {
  return coordinates_;
}

void CoordinatesBase::MoveBy(Vector2D coordinates) {
  coordinates_ += coordinates;
}
