#pragma once

#include "engine/system.h"

class Coordinator;

class AnimationSystem : public System {
 public:
  explicit AnimationSystem(Coordinator* coordinator);
  void Update();

 private:
  void HandleMovingAnimation(Entity entity);
  void HandleStaticAnimation(Entity entity);
  void HandleSpecialAnimation(Entity entity);

  void SetAnimation(Entity, AnimationType::TypeID);

  Coordinator* coordinator_;
  uint64_t timestamp_;
};
