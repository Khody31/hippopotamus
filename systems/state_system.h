#pragma once
#include "engine/system.h"

class StateSystem : public System {
 public:
  explicit StateSystem(Coordinator* coordinator);
  void Update();

 private:
  Coordinator* coordinator_;
};

