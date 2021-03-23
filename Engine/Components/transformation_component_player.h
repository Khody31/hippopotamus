#pragma once

#include "Engine/Misc/vector_2d.h"
#include "Engine/Components/Interfaces/transformation_component_interface.h"
#include <vector>

class TransformationComponentPlayer : public TransformationComponentInterface {
 public:
  virtual void Update() override;

  void SetX(double x) override;
  void SetY(double y) override;
  void SetCoordinates(Vector2D coordinates) override;
  void MoveBy(Vector2D coordinates) override;

  [[nodiscard]] Vector2D GetCoordinates() const override;

 private:
  Vector2D coordinates_{0,0};
};
