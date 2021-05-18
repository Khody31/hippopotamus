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
  kStupidBot,
  kCleverBot
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
