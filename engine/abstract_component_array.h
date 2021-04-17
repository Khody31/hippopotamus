#pragma once

#include "types.h"

// is necessary to let ComponentManager interact with ComponentArray

class AbstractComponentArray {
 public:
  virtual ~AbstractComponentArray() = default;
  virtual void DestroyEntity(Entity entity) = 0;
};
