#pragma once

#include <QVector2D>
#include <QPixmap>

#include "core/descriptions.h"

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
  QVector2D pos;
  QVector2D velocity;
};

struct MotionComponent {
  float initial_speed = 0;
  float speed = 0;
  QVector2D direction;
};

enum class EntityType;
struct SerializationComponent {
  EntityType type;
};

struct DoorComponent {
  int32_t room_id = 0;
  QVector2D next_player_pos;
};

struct HealthComponent {
  float value = 0;
};

struct DamageComponent {
  float value = 0;
};

enum class IntelligenceType {
  kStupid,
  kStanding,
  kClever
};

struct IntelligenceComponent {
  IntelligenceType type;
};
