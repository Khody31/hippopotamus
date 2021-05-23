#pragma once

#include <QVector2D>
#include <QPixmap>
#include <vector>

#include "core/descriptions.h"
#include "core/animation_pack.h"

enum class BulletType {
  kSimple,
  kStrongStone,
  kFireball
};
struct BulletComponent {
  BulletType type = BulletType::kSimple;
  int num_of_wall_hits = 0;
};

struct WallComponent{};

struct JoystickComponent {};

struct GarbageComponent {};

struct TransformationComponent {
  QVector2D position;
};

enum class Layer {
  lvl_0,
  lvl_1,
  lvl_2,
  lvl_3,
  lvl_4,
  lvl_5,
  lvl_6,
  kNumOfLayers
};
struct PixmapComponent {
  QVector2D size;
  const QPixmap* pixmap = nullptr;
  Layer layer = Layer::lvl_0;
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

// The order in enum should be like this.
enum class BuffType {
  kStrongStone,
  kFireball,
  kEnumSize
};
struct ArtifactComponent {
  BuffType buff_type;
  int existing_time = 0;
};
enum class StateType /*for enemies*/ {
  // todo (cool-down state for enemies)
};
struct StateComponent {
  std::vector<int> buff_to_time;
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
