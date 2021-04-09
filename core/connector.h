#pragma once

#include "engine/coordinator.h"
#include "systems/transformation_system.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();
 private:
  Coordinator game_coordinator_;
};