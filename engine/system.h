#pragma once

#include <unordered_set>
#include <set>

#include "types.h"

class System {
 public:
  System();

  std::unordered_set<Entity> entities_;
};
