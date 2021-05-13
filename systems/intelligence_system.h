#pragma once

#include <components/components.h>
#include "engine/coordinator.h"

class Connector;

class IntelligenceSystem : public System {
 public:
  IntelligenceSystem(Connector* connector, Coordinator* coordinator);
  void Update();
  void SetPlayer(Entity player);

 private:
  Entity player_;
  Connector* connector_;
  Coordinator* coordinator_;
};
