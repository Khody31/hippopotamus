#pragma once

#include <QVector2D>
#include <QPixmap>

#include "core/descriptions.h"
#include "core/animation_pack.h"
#include "core/constants.h"

struct BulletComponent {};

struct WallComponent{};

struct JoystickComponent {};

struct GarbageComponent {};

struct TransformationComponent {
  QVector2D position;
};

namespace SceneLayers {
enum LayerID {
  kFloor,
  kDoors,
  kForeground,
  kBottomDoor,

  kEnumSize
};
}

struct PixmapComponent {
  QVector2D size;
  const QPixmap* pixmap = nullptr;
  SceneLayers::LayerID layer = SceneLayers::kForeground;
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
  float max_health = 0;
  float value = max_health;
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

enum class AnimationPackType {
    kStatic,
    kMoving
};

struct AnimationComponent {
  AnimationPackType type;
  const AnimationPack* animations;

  AnimationType current_animation = AnimationType::kIdle;
  uint64_t last_switch_timestamp = 0;
};
