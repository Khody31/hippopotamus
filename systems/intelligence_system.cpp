#include "intelligence_system.h"
#include "core/connector.h"
#include "core/utility.h"
#include "core/constants.h"
#include <qdebug.h>

IntelligenceSystem::IntelligenceSystem(Connector* connector, Coordinator* coordinator) : connector_(
    connector), coordinator_(coordinator) {}

void AvoidObstacle(Entity bot, Entity obstacle, Coordinator* coordinator) {
  QVector2D distance =
      coordinator->GetComponent<TransformationComponent>(obstacle).pos -
          coordinator->GetComponent<TransformationComponent>(bot).pos;
  auto& motion = coordinator->GetComponent<MotionComponent>(bot);
  if (utility::AngleBetweenVecsCosine(distance, motion.direction) <
      game_constants::safe_angle_cosine) {
    return;
  }
  double diff_coefficient = distance.length() - game_constants::safe_distance;
  QVector2D avoidance_vec = -1 *
      game_constants::degree_of_avoidance *
      motion.speed *
      diff_coefficient *
      distance;
  utility::TurnVector90Degrees(&avoidance_vec);
  motion.direction = (motion.direction + avoidance_vec).normalized();
}

void ApplyStupidTactic(QVector2D player_pos, Coordinator* coordinator, Entity
entity) {
  auto& motion = coordinator->GetComponent<MotionComponent>(entity);
  auto& transform =
      coordinator->GetComponent<TransformationComponent>(entity);
  motion.direction = (player_pos - transform.pos).normalized();
  motion.speed = 0.7;
}

void ApplyStandingTactic(Coordinator* coordinator, Entity entity) {
  auto& motion = coordinator->GetComponent<MotionComponent>(entity);
  motion.speed = 0;
}

void ApplyCleverTactic(QVector2D player_pos, Coordinator* coordinator,
                       Entity entity, Connector* connector) {
  auto& motion = coordinator->GetComponent<MotionComponent>(entity);
  auto& transform = coordinator->GetComponent<TransformationComponent>
      (entity);
  auto& intelligence = coordinator->GetComponent<IntelligenceComponent>(entity);
  auto& collision_comp = coordinator->GetComponent<CollisionComponent>(entity);
  motion.direction = (player_pos - transform.pos).normalized();
  motion.speed = 0.4;
  // detect collisions of visibility area
  auto colliders = connector->GetEntitiesToCollide();
  for (const auto& collider : colliders) {
    if (coordinator->HasComponent<JoystickComponent>(collider) ||
        (collider == entity)) {
      continue;
    }
    // make collision component for visibility area
    CollisionComponent visibility_area{
        1, 1,
        3 * collision_comp.size,
        collision_comp.pos
    };
    utility::Collision collision{
        &visibility_area,
        &coordinator->GetComponent<CollisionComponent>(collider),
    };
    if (utility::IsCollisionPresent(&collision)) {
      AvoidObstacle(entity, collider, coordinator);
    }
  }
}

void IntelligenceSystem::Update() {
  QVector2D player_pos =
      coordinator_->GetComponent<TransformationComponent>(player_).pos;
  for (const auto& entity : entities_) {
    switch (coordinator_->GetComponent<IntelligenceComponent>(entity).type) {
      case IntelligenceType::kStupid : {
        ApplyStupidTactic(player_pos, coordinator_, entity);
        break;
      }
      case IntelligenceType::kStanding : {
        ApplyStandingTactic(coordinator_, entity);
        break;
      }
      case IntelligenceType::kClever : {
        ApplyCleverTactic(player_pos, coordinator_, entity, connector_);
        break;
      }
      default: {
        return;
      }
    }
  }
}

void IntelligenceSystem::SetPlayer(Entity player) {
  player_ = player;
}
