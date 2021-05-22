#pragma once

#include <array>
#include <vector>

#include <QVector2D>

enum class EntityType {
  kPlayer,
  kWall,
  kBall,
  kDoor,
  kUnknown,
  kAngryPlant,
  kLittleSkeleton,
  kCleverBot,
  kSmellingPlant,
  kBigSkeleton,
  kShootingBoss
};

struct EntityDescription {
  EntityType type = EntityType::kUnknown;
  QVector2D position;
};

struct RoomDescription {
  int32_t id = 0;
  std::array<int32_t, 4> connected_rooms{};
  std::vector<EntityDescription> descriptions;
};
