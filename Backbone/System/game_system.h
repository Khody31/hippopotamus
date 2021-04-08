#pragma once

#include <set>

using Entity = uint8_t;

class System
{
 public:
  std::set<Entity> mEntities;
};