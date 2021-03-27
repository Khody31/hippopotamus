#pragma once

#include "Engine/Components/Interfaces/transformation_component_interface.h"

class TransformationComponentBullet : public TransformationComponentInterface {
 public:
  void Update() override;
};
