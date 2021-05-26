#pragma once

#include <QVector2D>
#include <QPixmap>
#include <vector>

#include "core/descriptions.h"
#include "engine/types.h"
#include "core/animation_pack.h"
#include "core/constants.h"

enum class BulletType {
  kStone,
  kStrongStone,
  kFireball
};
struct BulletComponent {
  BulletType type = BulletType::kStone;
  Entity producer;
  int num_of_wall_hits = 0;
};

struct WallComponent {};

struct JoystickComponent {};

struct GarbageComponent {};

struct TransformationComponent {
  QVector2D position;
};

enum class SceneLayers {
  kBackground,
  kTutorial,
  kDecor,
  kDoors,
  kForeground,
  kBottomDoor,

  kEnumSize
};


struct PixmapComponent {
  QVector2D size;
  const QPixmap* pixmap = nullptr;
  SceneLayers layer = SceneLayers::kForeground;
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
  QVector2D position;
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
  // stands still and perform knockback for player
  kRepulsive,
  // follows player with obstacle avoidance
  kClever,
  // stands still and hit player in emitting area
  kEmitting,
  // produce little enemies
  kReproductive,
  // shoot player
  kShooting
};

struct IntelligenceComponent {
  IntelligenceType type;
};

namespace BuffType {
enum Buff {
  kStrongStone,
  kFireball,

  kEnumSize,

  kHealingPotion
};
}
struct ArtifactComponent {
  BuffType::Buff buff_type;
  int32_t lifetime = 0;
};

namespace EnemyState {
enum State {
  kCoolDown,
  kEnumSize
};

}
struct StateComponent {
  std::vector<int32_t> buff_to_time;
};

enum class AnimationPackType {
  kStatic,
  kMoving
};

struct AnimationComponent {
  AnimationPackType type;
  const AnimationPack* animations;

  bool on_special_animation;

  AnimationType::TypeID current_animation = AnimationType::kIdle;
  uint64_t last_switch_timestamp = 0;

  void PlaySpecial() {
    on_special_animation = true;
    last_switch_timestamp = 0;
  }
};
