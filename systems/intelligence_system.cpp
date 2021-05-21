#include "core/connector.h"
#include "core/utilities/transformation.h"
#include "core/constants.h"
#include "core/utilities/collisions.h"
#include "intelligence_system.h"

IntelligenceSystem::IntelligenceSystem(CollisionSystem* collision_system,
                                       Coordinator*coordinator,
                                       Entity* player) :
                                       collision_system_(collision_system),
                                        coordinator_(coordinator),
                                        player_(player) {}

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
  motion.speed = 0.7;
}

void IntelligenceSystem::ApplyStandingTactic(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  motion.speed = 0;
}

void IntelligenceSystem::ApplyCleverTactic(Entity entity) {
  auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
  auto& transform = coordinator_->GetComponent<TransformationComponent>(entity);
  auto& collision_comp = coordinator_->GetComponent<CollisionComponent>(entity);

  QVector2D player_position =
      coordinator_->GetComponent<TransformationComponent>(*player_).pos;

  motion.direction = (player_position - transform.pos).normalized();
  motion.speed = 0.4;

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
      default: {
        return;
      }
    }
  }
}
