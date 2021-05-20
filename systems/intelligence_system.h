#pragma once

#include <components/components.h>
#include "engine/coordinator.h"

class Connector;

class IntelligenceSystem : public System {
 public:
  IntelligenceSystem(CollisionSystem* collision_system,
                     Coordinator* coordinator,
                     Entity* entity,
                     Keyboard* keyboard);

  void Update();

 private:
  void ApplyStupidTactic(Entity entity);
  void ApplyStandingTactic(Entity entity);
  void ApplyCleverTactic(Entity entity);
  void AvoidObstacle(Entity bot, Entity obstacle);

  CollisionSystem* collision_system_;
  Entity* player_;
  Coordinator* coordinator_;
  Keyboard* keyboard_;
};
