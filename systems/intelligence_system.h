#pragma once

#include "components/components.h"
#include "core/random_generator.h"
#include "engine/coordinator.h"

class Connector;

class IntelligenceSystem : public System {
 public:
  IntelligenceSystem(CollisionSystem* collision_system,
                     Coordinator* coordinator,
                     Entity* entity,
                     Keyboard* keyboard,
                     Spawner* spawner,
                     Connector* connector);

  void Update();

 private:
  void ApplyPulsingTactic(Entity entity);
  void ApplyCleverTactic(Entity entity);
  void ApplyEmittingTactic(Entity entity);
  void ApplyReproductiveTactic(Entity entity);
  void ApplyShootingTactic(Entity entity);

  void Move(Entity entity);
  void ShootPlayer(Entity entity);
  void AvoidObstacle(Entity entity, Entity obstacle);
  void Reproduce(Entity bot);

  CollisionSystem* collision_system_;
  Entity* player_;
  Coordinator* coordinator_;
  Keyboard* keyboard_;
  Spawner* spawner_;
  RandomGenerator random_;
  Connector* connector_;
};
