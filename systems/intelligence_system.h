#pragma once

#include <components/components.h>
#include "engine/coordinator.h"

class Connector;

class IntelligenceSystem : public System {
 public:
  IntelligenceSystem(Connector* connector,
                     Coordinator* coordinator,
                     Entity* entity);

  void Update();

 private:
  void ApplyStupidTactic(Entity entity);
  void ApplyStandingTactic(Entity entity);
  void ApplyCleverTactic(Entity entity);
  void AvoidObstacle(Entity bot, Entity obstacle, Coordinator* coordinator);

  Entity* player_;
  Connector* connector_;
  Coordinator* coordinator_;
};
