#include <QTimer>

#include "core/connector.h"
#include "utilities/transformation.h"
#include "utilities/collisions.h"
#include "core/constants.h"
#include "intelligence_system.h"
#include "core/random_generator.h"

IntelligenceSystem::IntelligenceSystem(CollisionSystem* collision_system,
                                       Coordinator* coordinator,
                                       Entity* player,
                                       Keyboard* keyboard,
                                       Spawner* spawner,
                                       Connector* connector) :
    collision_system_(collision_system),
    coordinator_(coordinator),
    player_(player),
    keyboard_(keyboard),
    spawner_(spawner),
    connector_(connector) {}

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

void IntelligenceSystem::Reproduce(Entity bot) {
  if (random_.RandomGenerator::GetInt(
      0, static_cast<int32_t>(4500 / constants::kTickTime)) == 0) {
    coordinator_->GetComponent<AnimationComponent>(bot).on_special_animation =
        true;
    connector_->PlaySound(GameSound::kWand);
    const QVector2D& player_pos =
        coordinator_->GetComponent<TransformationComponent>(*player_).position;
    for (int32_t i = 0; i < 3; ++i) {
      QVector2D spawn_pos = random_.GetPositionAvoidingDoors();
      while (spawn_pos.distanceToPoint(player_pos) < 0.4) {
        spawn_pos = random_.GetPositionAvoidingDoors();
      }
      spawner_->CreateLittleSkeleton(spawn_pos);
    }
  }
}

void IntelligenceSystem::ShootPlayer(Entity bot) {
  if (random_.RandomGenerator::GetInt(
      0, static_cast<int32_t>(42 * constants::kTickTime)) == 0) {
    spawner_->CreateBullet(
        bot,
        coordinator_->GetComponent<TransformationComponent>(*player_).position);
  }
}

void IntelligenceSystem::ApplyPulsingTactic(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  motion.current_speed = motion.initial_speed;

  auto& collision_comp = coordinator_->GetComponent<CollisionComponent>(entity);
  auto colliders = collision_system_->GetEntities();
  CollisionComponent pulsing_area{
      1, 1,
      2 * collision_comp.size,
      collision_comp.position
  };
  utility::Collision collision{
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
    float damage = coordinator_->GetComponent<DamageComponent>(entity).value;
    coordinator_->GetComponent<HealthComponent>(*player_).value -= damage;
    connector_->PlaySound(GameSound::kPlayerHit);

    QTimer::singleShot(constants::kSingleShotTime,
                       keyboard_,
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
  utility::Collision collision{
      &emitting_area,
      &coordinator_->GetComponent<CollisionComponent>(*player_),
  };
  if (IsCollisionPresent(&collision)) {
    // hit player
    float damage = coordinator_->GetComponent<DamageComponent>(entity).value;
    coordinator_->GetComponent<HealthComponent>(*player_).value -= damage;
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

    utility::Collision physical_collision{
        &visibility_area,
        &coordinator_->GetComponent<CollisionComponent>(collider),
    };

    if (IsCollisionPresent(&physical_collision)) {
      AvoidObstacle(entity, collider);
    }
  }
}

void IntelligenceSystem::ApplyReproductiveTactic(Entity entity) {
  Reproduce(entity);

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
        2 * collision.size,
        collision.position
    };

    utility::Collision physical_collision{
        &visibility_area,
        &coordinator_->GetComponent<CollisionComponent>(collider),
    };

    if (IsCollisionPresent(&physical_collision)) {
      AvoidObstacle(entity, collider);
    }
  }
}

void IntelligenceSystem::ApplyShootingTactic(Entity entity) {
  Move(entity);
  ShootPlayer(entity);

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
        2 * collision.size,
        collision.position
    };
    utility::Collision physical_collision{
        &visibility_area,
        &coordinator_->GetComponent<CollisionComponent>(collider),
    };

    if (IsCollisionPresent(&physical_collision)) {
      AvoidObstacle(entity, collider);
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
      case IntelligenceType::kShooting : {
        ApplyShootingTactic(entity);
        break;
      }
    }
  }
}
