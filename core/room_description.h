#pragma once

#include "entity_description.h"
#include "engine/types.h"

#include <vector>
#include <array>

struct RoomDescription {
  int32_t id;
  std::vector<EntityDescription> descriptions;
  std::array<int32_t, 4> connected_rooms{};
};
