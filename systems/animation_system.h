#pragma once

#include "engine/system.h"

class Connector;
class Coordinator;

class AnimationSystem : public System {
 public:
  AnimationSystem(Coordinator* coordinator);
  void Update();

 private:
  void HandleMovingAnimation(Entity entity);
  void HandleStaticAnimation(Entity entity);

  Coordinator* coordinator_;
  uint64_t current_time_;
};
