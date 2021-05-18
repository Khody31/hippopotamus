#pragma once

#include <QVector2D>
#include <QPixmap>
#include <vector>

#include "core/descriptions.h"
#include "animation.h"

struct IntelligenceComponent {};

struct BulletComponent {};

struct JoystickComponent {};

struct TransformationComponent {
  QVector2D pos;
};

struct PixmapComponent {
  const QPixmap* pixmap = nullptr;
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

struct AnimationComponent {
  enum Type {
    kStatic,
    kMoving
  };
  enum State {
    kIdle,
    kRight,
    kLeft,
    kDown,
    kUp
  };
  Type type;
  std::vector<Animation*> animations = {};

  size_t current = 0;
  uint64_t last_switch_timestamp = 0;
};
