#include "coordinates_base.h"

void CoordinatesBase::OnMove() {
  for (auto listener : listeners_) {
    listener->OnMove();
  }
}

void CoordinatesBase::SetX(double x) {
  coordinates_.x = x;
  OnMove();
}

void CoordinatesBase::SetY(double y) {
  coordinates_.y = y;
  OnMove();
}

void CoordinatesBase::SetCoordinates(Vector2D coordinates) {
  coordinates_ = coordinates;
  OnMove();
}

Vector2D CoordinatesBase::GetCoordinates() const {
  return coordinates_;
}
