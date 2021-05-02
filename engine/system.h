#pragma once

#include <unordered_set>

#include "types.h"

class Coordinator;

class System {
 public:
  std::unordered_set<Entity> entities_;
};
