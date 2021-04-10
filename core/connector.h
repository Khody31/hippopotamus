#pragma once

#include "engine/coordinator.h"
#include "systems/transformation_system.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();
  void OnTick();
 private:
  Coordinator game_coordinator_;
  std::shared_ptr<TransformationSystem> tr_system_;
};