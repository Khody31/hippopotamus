#include "transformation_component.h"

void TransformationComponent::SetX(double x) {
  coordinates_.x = x;
}

void TransformationComponent::SetY(double y) {
  coordinates_.y = y;
}

void TransformationComponent::SetCoordinates(Vector2D coordinates) {
  coordinates_ = coordinates;
}

Vector2D TransformationComponent::GetCoordinates() const {
  return coordinates_;
}

void TransformationComponent::MoveBy(Vector2D coordinates) {
  coordinates_ += coordinates;
}
