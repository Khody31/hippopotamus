#pragma once

#include "Engine/Components/Interfaces/transformation_component_interface.h"
#include <vector>
#include <iostream>

class TransformationComponentPlayer : public TransformationComponentInterface {
 public:
  virtual void Update() override;
};
