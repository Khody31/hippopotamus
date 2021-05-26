#pragma once

#include <array>
#include <vector>

#include <QVector2D>

enum class EntityType {
  kPlayer,
  kWall,
  kDoor,
  kUnknown,
  kBouncingTotem,
  kLittleSkeleton,
  kWasp,
  kBattleTotem,
  kDecorative1,
  kDecorative2,
  kDecorative3,
  kDecorative4,
  kDecorative5,
  kDecorative6,
  kDecorative7,
  kDecorative8,
  kDecorative9,
  kDecorative10,
  kDecorative11,
  kDecorative12,
  kDecorative13,
  kDecorative14,
  kDecorative15,
  kPile1,
  kPile2,
  kPile3,
  kPile4,
  kPile5,
  kNecromancer,
  kShootingBoss,
  kTutorial
};

struct EntityDescription {
  EntityDescription(EntityType type, QVector2D position) :
      type(type), position(position) {}

  EntityType type = EntityType::kUnknown;
  QVector2D position;
};

struct RoomDescription {
  int32_t id = 0;
  std::array<int32_t, 4> connected_rooms{};
  std::vector<EntityDescription> descriptions;
};
