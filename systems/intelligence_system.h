#pragma once

#include <components/components.h>
#include "engine/coordinator.h"

class Connector;

class IntelligenceSystem : public System {
 public:
  IntelligenceSystem(CollisionSystem* collision_system,
                     Coordinator* coordinator,
                     Entity* entity,
                     Keyboard* keyboard,
                     Spawner* spawner);

  void Update();

 private:
  void ApplyStupidTactic(Entity entity);
  void ApplyPulsingTactic(Entity entity);
  void ApplyCleverTactic(Entity entity);
  void ApplyEmittingTactic(Entity entity);
  void ApplyReproductiveTactic(Entity entity);

  void MoveSmart(Entity entity);
  void Move(Entity entity);
  void StandStill(Entity entity);

  void AvoidObstacle(Entity bot, Entity obstacle);
  void Reproduct(Entity bot);

  CollisionSystem* collision_system_;
  Entity* player_;
  Coordinator* coordinator_;
  Keyboard* keyboard_;
  Spawner* spawner_;
};
