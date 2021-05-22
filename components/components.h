#pragma once

#include <QVector2D>
#include <QPixmap>

#include "core/descriptions.h"

enum class BulletType {
  kSimple,
  kFireball
};
struct BulletComponent {
  BulletType type = BulletType::kSimple;
  int num_of_wall_hits = 0;
  static constexpr int max_num_of_wall_hits = 4;
};

struct WallComponent{};

struct JoystickComponent {};

struct GarbageComponent {};

struct TransformationComponent {
  QVector2D position;
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
  float initial_speed = 0;
  QVector2D direction;
  float current_speed = initial_speed;
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

enum class BuffType {
  kFireball,

  kEnumSize,
  kNone
};
struct ArtifactComponent {
  BuffType buff_type;
  int existing_time = 0;
};
