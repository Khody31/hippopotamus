#pragma once

#include "engine/system.h"

class Connector;
class Coordinator;

class AnimationSystem : public System {
 public:
  AnimationSystem(Connector* connector,
                  Coordinator* coordinator);
  void Update();

 private:
  Connector* connector_;
  Coordinator* coordinator_;

  uint64_t current_time_;
};
