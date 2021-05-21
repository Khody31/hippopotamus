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
  MotionComponent() {}
  MotionComponent(float speed) : initial_speed(speed),
                                 current_speed(speed) {}
  MotionComponent(float speed, QVector2D direction) : initial_speed(speed),
                                                      current_speed(speed),
                                                      direction(direction) {}
  float initial_speed = 0;
  float current_speed = 0;
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
  // follows player without avoidance
  kStupid,
  // stands still and perform knockback for player
  kRepulsive,
  // follows player with obstacle avoidance
  kClever,
  // stands still and hit player in emitting area
  kEmitting
};

struct IntelligenceComponent {
  IntelligenceType type;
};
