#include <QTimer>

#include "core/connector.h"
#include "core/utility.h"
#include "core/constants.h"
#include "core/collisions.h"
#include "intelligence_system.h"

IntelligenceSystem::IntelligenceSystem(CollisionSystem* collision_system,
                                       Coordinator* coordinator,
                                       Entity* player,
                                       Keyboard* keyboard) :
    collision_system_(collision_system),
    coordinator_(coordinator),
    player_(player),
    keyboard_(keyboard) {}

void IntelligenceSystem::AvoidObstacle(Entity bot,
                                       Entity obstacle) {
  QVector2D distance =
      coordinator_->GetComponent<TransformationComponent>(obstacle).pos -
          coordinator_->GetComponent<TransformationComponent>(bot).pos;
  auto& motion = coordinator_->GetComponent<MotionComponent>(bot);

  if (utility::CalculateAngle(distance, motion.direction) <
      constants::kSafeAngleCosine) {
    return;
  }

  float difference = distance.length() - constants::kSafeDistance;
  QVector2D avoidance = -1 * constants::kDegreeOfAvoidance *
      motion.speed * difference * distance;
  utility::TurnVector(&avoidance);
  motion.direction = (motion.direction + avoidance).normalized();
}

void IntelligenceSystem::ApplyStupidTactic(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  auto& transform = coordinator_->GetComponent<TransformationComponent>(entity);

  QVector2D player_position =
      coordinator_->GetComponent<TransformationComponent>(*player_).pos;

  motion.direction = (player_position - transform.pos).normalized();
  motion.speed = motion.initial_speed;
}

void IntelligenceSystem::ApplyStandingTactic(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  motion.speed = motion.initial_speed;

  auto& collision_comp = coordinator_->GetComponent<CollisionComponent>(entity);
  auto colliders = collision_system_->GetEntities();
  // detect collisions of visibility area
  // make collision component for visibility area
  CollisionComponent visibility_area{
      1, 1,
      1.5 * collision_comp.size,
      collision_comp.pos
  };
  Collision collision{
      &visibility_area,
      &coordinator_->GetComponent<CollisionComponent>(*player_),
  };
  if (IsCollisionPresent(&collision)) {
    keyboard_->Block();

    // throw player away
    QVector2D bot_position =
        coordinator_->GetComponent<TransformationComponent>(entity).pos;
    QVector2D player_position =
        coordinator_->GetComponent<TransformationComponent>(*player_).pos;
    coordinator_->GetComponent<MotionComponent>(*player_).direction =
        (player_position - bot_position).normalized();

    // hit player
    float damage =
        coordinator_->GetComponent<DamageComponent>(entity).value;
    coordinator_->
        GetComponent<HealthComponent>(*player_).value -= damage;

    QTimer::singleShot(200, keyboard_, &Keyboard::Unblock);
  }
}

void IntelligenceSystem::ApplyCleverTactic(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  auto& transform = coordinator_->GetComponent<TransformationComponent>(entity);
  auto& collision_comp = coordinator_->GetComponent<CollisionComponent>(entity);

  QVector2D player_position =
      coordinator_->GetComponent<TransformationComponent>(*player_).pos;

  motion.direction = (player_position - transform.pos).normalized();
  motion.speed = motion.initial_speed;

  auto colliders = collision_system_->GetEntities();
  // detect collisions of visibility area
  for (const auto& collider : colliders) {
    if (coordinator_->HasComponent<JoystickComponent>(collider) ||
        (collider == entity)) {
      continue;
    }
    // make collision component for visibility area
    CollisionComponent visibility_area{
        1, 1,
        3 * collision_comp.size,
        collision_comp.pos
    };
    Collision collision{
        &visibility_area,
        &coordinator_->GetComponent<CollisionComponent>(collider),
    };
    if (IsCollisionPresent(&collision)) {
      AvoidObstacle(entity, collider);
    }
  }
}

void IntelligenceSystem::Update() {
  for (const auto& entity : entities_) {
    switch (coordinator_->GetComponent<IntelligenceComponent>(entity).type) {
      case IntelligenceType::kStupid : {
        ApplyStupidTactic(entity);
        break;
      }
      case IntelligenceType::kStanding : {
        ApplyStandingTactic(entity);
        break;
      }
      case IntelligenceType::kClever : {
        ApplyCleverTactic(entity);
        break;
      }
      default:return;
    }
  }
}

