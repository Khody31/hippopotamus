#pragma once

#include "engine/components/interfaces/transformation_component_interface.h"

class TransformationComponentBullet : public TransformationComponentInterface {
 public:
  void Update() override;
};
