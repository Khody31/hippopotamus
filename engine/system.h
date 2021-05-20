#pragma once

#include <unordered_set>

#include "types.h"

class System {
 public:
  std::unordered_set<Entity> entities_;
};
