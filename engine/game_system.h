#pragma once

#include <set>

#include "types.h"

class Coordinator;

class System {
 public:
  virtual void Update(Coordinator* coordinator) = 0;

  std::set<Entity> entities_;
};
