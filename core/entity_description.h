#pragma once

#include <bitset>

#include "components/components.h"

enum class EntityType {
    kPlayer,
    kWall,
    kBall,
    kDoor,
    kUnknown,
    kEnemy
};

struct EntityDescription {
  EntityType type = EntityType::kUnknown;
  QVector2D pos;
};
