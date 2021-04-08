#pragma once

#include <cstdint>

using Entity = uint8_t;

// is necessary to let ComponentManager interact with ComponentArray when entity
// is destroying

class ComponentArrayInterface
{
 public:
  virtual ~ComponentArrayInterface() = default;
  virtual void EntityDestroyed(Entity entity) = 0;
};
