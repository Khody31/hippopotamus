#pragma once

#include "engine/coordinator.h"

class TransformationSystem : public System {
 public:
  void Update(Coordinator* coordinator) override;
};
