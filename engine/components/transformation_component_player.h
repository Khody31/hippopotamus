#pragma once

#include "engine/components/interfaces/transformation_component_interface.h"
#include <vector>
#include <iostream>

class TransformationComponentPlayer : public TransformationComponentInterface {
 public:
  void Update() override;
};
