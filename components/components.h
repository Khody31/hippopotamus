#pragma once

#include <QVector2D>
#include <QPixmap>

#include "core/descriptions.h"

struct IntelligenceComponent {};

struct BulletComponent {};

struct JoystickComponent {};

struct TransformationComponent {
  QVector2D pos;
};

struct PixmapComponent {
  QPixmap pixmap;
  QVector2D size;
};

struct CollisionComponent {
  float inverted_mass = 0;
  float elasticity = 0;

  QVector2D size;
  QVector2D position;
  QVector2D velocity;
};

struct MotionComponent {
  float speed = 0;
  QVector2D direction;
};

enum class EntityType;
struct SerializationComponent {
  EntityType type;
};

struct DoorComponent {
  int32_t room_id = 0;
  QVector2D player_position;
};

struct HealthComponent {
  float value = 0;
};

struct DamageComponent {
  float value = 0;
};
