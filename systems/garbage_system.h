#pragma once

#include "engine/system.h"

// This system stores entities which should be deleted when changing a room.
// For example, bullets.
class GarbageSystem : public System {
 public:
  GarbageSystem() = default;
};
