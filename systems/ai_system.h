#pragma once

#include <components/components.h>
#include "engine/coordinator.h"

class Connector;

class AiSystem : public System {
 public:
  AiSystem(Connector* connector, Coordinator* coordinator);
  void Update();
  void SetPlayer(Entity player);

 private:
  Entity player_;
  Connector* connector_;
  Coordinator* coordinator_;
};
