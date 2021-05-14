#pragma once

#include <vector>
#include <array>
#include <bitset>

#include "components/components.h"

enum class EntityType {
    kPlayer,
    kWall,
    kBall,
    kDoor,
    kUnknown
};

struct EntityDescription {
  EntityType type = EntityType::kUnknown;
  QVector2D pos;
};

struct RoomDescription {
  int32_t id;
  std::vector<EntityDescription> descriptions;
  std::array<int32_t, 4> connected_rooms{};
};
