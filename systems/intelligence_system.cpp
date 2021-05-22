#include <QTimer>

#include "core/connector.h"
#include "core/utility.h"
#include "core/constants.h"
#include "core/collisions.h"
#include "intelligence_system.h"

IntelligenceSystem::IntelligenceSystem(CollisionSystem* collision_system,
                                       Coordinator* coordinator,
                                       Entity* player,
                                       Keyboard* keyboard,
                                       Spawner* spawner) :
    collision_system_(collision_system),
    coordinator_(coordinator),
    player_(player),
    keyboard_(keyboard),
    spawner_(spawner) {}

void IntelligenceSystem::Move(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  auto& transform = coordinator_->GetComponent<TransformationComponent>(entity);

  QVector2D player_position =
      coordinator_->GetComponent<TransformationComponent>(*player_).position;

  motion.direction = (player_position - transform.position).normalized();
  motion.current_speed = motion.initial_speed;
}

void IntelligenceSystem::AvoidObstacle(Entity bot,
                                       Entity obstacle) {
  QVector2D distance =
      coordinator_->GetComponent<TransformationComponent>(obstacle).position
          - coordinator_->GetComponent<TransformationComponent>(bot).position;
  auto& motion = coordinator_->GetComponent<MotionComponent>(bot);

  if (utility::CalculateAngle(distance, motion.direction) <
      constants::kSafeAngleCosine) {
    return;
  }

  float difference = distance.length() - constants::kSafeDistance;
  QVector2D avoidance = -1 * constants::kDegreeOfAvoidance *
      motion.current_speed * difference * distance;
  utility::TurnVector(&avoidance);
  motion.direction = (motion.direction + avoidance).normalized();
}

void IntelligenceSystem::Reproduct(Entity bot) {
  // TODO(polchenikova) : apply random generator from map-generation
  if (rand() % 210 == 0) {
    spawner_->CreateLittleSkeleton(
    coordinator_->GetComponent<TransformationComponent>(bot).position);
  }
}

void IntelligenceSystem::ApplyPulsingTactic(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  motion.current_speed = motion.initial_speed;

  auto& collision_comp = coordinator_->GetComponent<CollisionComponent>(entity);
  auto colliders = collision_system_->GetEntities();
  CollisionComponent pulsing_area{
      1, 1,
      1.5 * collision_comp.size,
      collision_comp.position
  };
  Collision collision{
      &pulsing_area,
      &coordinator_->GetComponent<CollisionComponent>(*player_),
  };
  if (IsCollisionPresent(&collision)) {
    keyboard_->Block();

    // throw player away
    QVector2D bot_position =
        coordinator_->GetComponent<TransformationComponent>(entity).position;
    QVector2D player_position =
        coordinator_->GetComponent<TransformationComponent>(*player_).position;
    coordinator_->GetComponent<MotionComponent>(*player_).direction =
        (player_position - bot_position).normalized();

    // hit player
    float damage =
        coordinator_->GetComponent<DamageComponent>(entity).value;
    coordinator_->
        GetComponent<HealthComponent>(*player_).value -= damage;

    QTimer::singleShot(constants::kSingleShotTime, keyboard_,
                       &Keyboard::Unblock);
  }
}

void IntelligenceSystem::ApplyEmittingTactic(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  motion.current_speed = motion.initial_speed;

  auto& collision_comp = coordinator_->GetComponent<CollisionComponent>(entity);
  auto colliders = collision_system_->GetEntities();

  CollisionComponent emitting_area{
      1, 1,
      2 * collision_comp.size,
      collision_comp.position
  };
  Collision collision{
      &emitting_area,
      &coordinator_->GetComponent<CollisionComponent>(*player_),
  };
  if (IsCollisionPresent(&collision)) {
    // hit player
    float damage =
        coordinator_->GetComponent<DamageComponent>(entity).value;
    coordinator_->
        GetComponent<HealthComponent>(*player_).value -= damage;
  }
}

void IntelligenceSystem::ApplyCleverTactic(Entity entity) {
  Move(entity);
  auto& collision = coordinator_->GetComponent<CollisionComponent>(entity);
  auto colliders = collision_system_->GetEntities();
  // detect collisions of visibility area
  for (const auto& collider : colliders) {
    if (coordinator_->HasComponent<JoystickComponent>(collider) ||
        coordinator_->HasComponent<WallComponent>(collider) ||
        coordinator_->HasComponent<DoorComponent>(collider)) {
      continue;
    }
    // make physical_collision component for visibility area
    CollisionComponent visibility_area{
        1, 1,
        3 * collision.size,
        collision.position
    };

    Collision physical_collision{
        &visibility_area,
        &coordinator_->GetComponent<CollisionComponent>(collider),
    };

    if (IsCollisionPresent(&physical_collision)) {
      AvoidObstacle(entity, collider);
    }
  }
}

void IntelligenceSystem::ApplyReproductiveTactic(Entity entity) {
  auto& collision = coordinator_->GetComponent<CollisionComponent>(entity);
  auto colliders = collision_system_->GetEntities();
  // detect collisions of visibility area
  for (const auto& collider : colliders) {
    if (coordinator_->HasComponent<JoystickComponent>(collider) ||
        coordinator_->HasComponent<WallComponent>(collider) ||
        coordinator_->HasComponent<DoorComponent>(collider)) {
      continue;
    }
    // make physical_collision component for visibility area
    CollisionComponent visibility_area{
        1, 1,
        3 * collision.size,
        collision.position
    };

    Collision physical_collision{
        &visibility_area,
        &coordinator_->GetComponent<CollisionComponent>(collider),
    };

    if (IsCollisionPresent(&physical_collision)) {
      AvoidObstacle(entity, collider);
      Reproduct(entity);
    }
  }
}

void IntelligenceSystem::Update() {
  for (const auto& entity : entities_) {
    switch (coordinator_->GetComponent<IntelligenceComponent>(entity).type) {
      case IntelligenceType::kRepulsive : {
        ApplyPulsingTactic(entity);
        break;
      }
      case IntelligenceType::kClever : {
        ApplyCleverTactic(entity);
        break;
      }
      case IntelligenceType::kEmitting : {
        ApplyEmittingTactic(entity);
        break;
      }
      case IntelligenceType::kReproductive : {
        ApplyReproductiveTactic(entity);
        break;
      }
      default:return;
    }
  }
}
