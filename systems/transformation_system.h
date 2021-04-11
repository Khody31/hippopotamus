#pragma once

#include "engine/coordinator.h"

class TransformationSystem : public System {
 public:
  void Update(Coordinator* game_coordinator) override;
};
