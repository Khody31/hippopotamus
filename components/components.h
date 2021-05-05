#pragma once

#include <QVector2D>
#include <QPixmap>

#include "core/entity_description.h"

struct TransformationComponent {
  QVector2D pos;
};

struct PixmapComponent {
  QPixmap pixmap;
  QVector2D size;
};

enum class CollisionType {
  kDefault,
  kRoomChanging,
  kPlayer
};

struct CollisionComponent {
  CollisionType type;
  // inverted mass = 1 / mass
  float inverted_mass = 0;
  float elasticity = 0;
  QVector2D size;
  QVector2D pos;
  QVector2D velocity;
};

struct JoystickComponent {};

struct MotionComponent {
  float speed = 0;
  QVector2D direction;
};

enum class EntityType;
struct SerializationComponent {
  EntityType type;
};

struct DoorComponent {
  uint32_t next_room_id;
  QVector2D move_player_to = {0, -0.7};
};
