#include "ai_system.h"
#include "core/connector.h"
#include "core/helpers.h"
#include "core/game_constants.h"
#include <qdebug.h>

void AvoidObstacle(Entity bot, Entity obstacle, Coordinator* coordinator) {
  QVector2D distance =
      coordinator->GetComponent<TransformationComponent>(obstacle).pos -
          coordinator->GetComponent<TransformationComponent>(bot).pos;
  auto& motion_comp = coordinator->GetComponent<MotionComponent>(bot);
  if (helpers::AngleBetweenVecsCosine(distance, motion_comp.direction) <
      game_constants::safe_angle_cosine) {
    return;
  }
  double diff_coefficient = distance.length() - game_constants::safe_distance;
  QVector2D avoidance_vec = -1 *
      game_constants::degree_of_avoidance *
      motion_comp.speed *
      diff_coefficient *
      distance;
  helpers::TurnVector90Degrees(avoidance_vec);
  motion_comp.direction = (motion_comp.direction + avoidance_vec).normalized();
}

void ApplyStupidTactic(QVector2D player_pos, Coordinator* coordinator, Entity
entity) {
  auto& motion_comp = coordinator->GetComponent<MotionComponent>(entity);
  auto& transform_comp =
      coordinator->GetComponent<TransformationComponent>(entity);
  motion_comp.direction = (player_pos - transform_comp.pos).normalized();
  motion_comp.speed = 0.7;
}

void ApplyStandingTactic(Coordinator* coordinator, Entity entity) {
  auto& motion_comp = coordinator->GetComponent<MotionComponent>(entity);
  motion_comp.speed = 0;
}

void ApplyCleverTactic(QVector2D player_pos, Coordinator* coordinator,
                       Entity entity,
                       Connector* connector) {
  auto& motion_comp = coordinator->GetComponent<MotionComponent>(entity);
  auto& transform_comp = coordinator->GetComponent<TransformationComponent>
      (entity);
  auto& ai_comp = coordinator->GetComponent<AiComponent>(entity);
  auto& collision_comp = coordinator->GetComponent<CollisionComponent>(entity);
  motion_comp.direction = (player_pos - transform_comp.pos).normalized();
  motion_comp.speed = 0.4;
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
        CollisionType::kEnemy,
        collision_comp.pos
    };
    helpers::Collision collision{
        &visibility_area,
        &coordinator->GetComponent<CollisionComponent>(collider),
    };
    if (helpers::IsCollisionPresent(&collision)) {
      AvoidObstacle(entity, collider, coordinator);
    }
  }
}

void AiSystem::Update(QVector2D player_pos, Coordinator* coordinator) {
  for (const auto& entity : entities_) {
    switch (coordinator->GetComponent<AiComponent>(entity).type) {
      case AiType::kStupid : {
        ApplyStupidTactic(player_pos, coordinator, entity);
        break;
      }
      case AiType::kStanding : {
        ApplyStandingTactic(coordinator, entity);
        break;
      }
      case AiType::kClever : {
        ApplyCleverTactic(player_pos, coordinator, entity, connector_);
        break;
      }
      default: {
        throw "Unknown enemy";
      }
    }
  }
}

void AiSystem::SetConnector(Connector* ptr) {
  connector_ = ptr;
}
