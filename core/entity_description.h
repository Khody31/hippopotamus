#pragma once

#include <bitset>

#include "components/components.h"

enum class EntityType {
    kPlayer,
    kWall,
    kStupidEnemy,
    kUnknown
};

struct EntityDescription {
  EntityType type = EntityType::kUnknown;
  QVector2D pos;
};
