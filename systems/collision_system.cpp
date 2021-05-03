#include "collision_system.h"
#include "components/components.h"
#include "core/connector.h"

#include <algorithm>
#include <utility>
#include <QVector2D>

struct Collision {
  CollisionComponent* fst_collider;
  CollisionComponent* scd_collider;
  float penetration;
  QVector2D normal;
};

std::pair<float, float> CalculateOverlaps(Collision* collision) {
  CollisionComponent* fst_collider = collision->fst_collider;
  CollisionComponent* scd_collider = collision->scd_collider;

  std::array<float, 2> result{};
  for (int i = 0; i < 2; ++i) {
    float fst_right = (fst_collider->pos + fst_collider->size / 2)[i];
    float scd_right = (scd_collider->pos + scd_collider->size / 2)[i];
    float fst_left = (fst_collider->pos - fst_collider->size / 2)[i];
    float scd_left = (scd_collider->pos - scd_collider->size / 2)[i];
    result[i] = std::min(fst_right, scd_right) - std::max(fst_left, scd_left);
  }
  return std::make_pair(result[0], result[1]);
}

bool IsCollisionExists(Collision* collision) {
  auto[x_overlap, y_overlap] = CalculateOverlaps(collision);
  QVector2D from_fst_to_scd = collision->scd_collider->pos
      - collision->fst_collider->pos;

  if (x_overlap > 0 && y_overlap > 0) {
    if (x_overlap < y_overlap) {
      if (from_fst_to_scd.x() < 0) {
        collision->normal = QVector2D(-1, 0);
      } else {
        collision->normal = QVector2D(1, 0);
      }
      collision->penetration = x_overlap;
      return true;
    } else {
      if (from_fst_to_scd.y() < 0) {
        collision->normal = QVector2D(0, -1);
      } else {
        collision->normal = QVector2D(0, 1);
      }
      collision->penetration = y_overlap;
      return true;
    }
  }
  return false;
}

void ResolveCollision(Collision* collision) {
  CollisionComponent* fst_comp = collision->fst_collider;
  CollisionComponent* scd_comp = collision->scd_collider;
  QVector2D normal = collision->normal;

  QVector2D relative_velocity = scd_comp->velocity - fst_comp->velocity;
  float velocity_along_normal = relative_velocity.x() * normal.x() +
      relative_velocity.y() * normal.y();

  // we don't solve the collision if it will be solved itself
  if (velocity_along_normal > 0) {
    return;
  }

  float elasticity = std::min(fst_comp->elasticity, scd_comp->elasticity);
  float impulse_module = -(1 + elasticity) * velocity_along_normal;
  impulse_module /= fst_comp->inverted_mass + scd_comp->inverted_mass;

  QVector2D impulse = impulse_module * normal;
  fst_comp->velocity -= fst_comp->inverted_mass * impulse;
  scd_comp->velocity += scd_comp->inverted_mass * impulse;
}

// needed to solve problem with drowning colliders
void PositionalCorrection(Collision* collision) {
  const float percent = 0.2;
  const float slop = 0.01;

  CollisionComponent* fst_collider = collision->fst_collider;
  CollisionComponent* scd_collider = collision->scd_collider;

  QVector2D correction = std::max(
      collision->penetration - slop, 0.0f) /
      (fst_collider->inverted_mass + scd_collider->inverted_mass)
      * percent * collision->normal;

  fst_collider->pos -= fst_collider->inverted_mass * correction;
  scd_collider->pos += scd_collider->inverted_mass * correction;
}

void CollisionSystem::UpdateCollisionComponents(Coordinator* coordinator) {
  // synchronize collision component's fields with other components
  for (auto entity : entities_) {
    auto& transform_comp =
        coordinator->GetComponent<TransformationComponent>(entity);
    auto& collision_comp =
        coordinator->GetComponent<CollisionComponent>(entity);
    auto& motion_comp =
        coordinator->GetComponent<MotionComponent>(entity);

    collision_comp.pos = transform_comp.pos;
    collision_comp.velocity = motion_comp.speed
        * motion_comp.direction.normalized();
  }
}

void CollisionSystem::UpdateOtherComponents(Coordinator* coordinator) {
  // synchronize other component's field with collision components
  for (auto entity : entities_) {
    auto& transform_comp =
        coordinator->GetComponent<TransformationComponent>(entity);
    auto& collision_comp =
        coordinator->GetComponent<CollisionComponent>(entity);
    auto& motion_comp =
        coordinator->GetComponent<MotionComponent>(entity);

    transform_comp.pos = collision_comp.pos;
    motion_comp.speed = collision_comp.velocity.length();
    motion_comp.direction = collision_comp.velocity.normalized();
  }
}

bool CollisionSystem::ResolveRoomChangingCollision(const DoorComponent& comp) {
  if (keyboard_->IsKeyPressed(KeyAction::kGeneralAction)) {
    connector_->ChangeRoom(comp);
    return true;
  }
  return false;
}

void CollisionSystem::Update(Coordinator* coordinator) {
  UpdateCollisionComponents(coordinator);

  for (auto fst_entity : entities_) {
    for (auto scd_entity : entities_) {
      if (fst_entity == scd_entity) {
        continue;
      }

      Collision collision{
          &coordinator->GetComponent<CollisionComponent>(fst_entity),
          &coordinator->GetComponent<CollisionComponent>(scd_entity),
      };

      if (IsCollisionExists(&collision)) {
        if (collision.fst_collider->type == CollisionType::kRoomChanging &&
           collision.scd_collider->type == CollisionType::kPlayer) {
          if (ResolveRoomChangingCollision(
              coordinator->GetComponent<DoorComponent>
              (fst_entity))) {
            return;
          }
        }

        ResolveCollision(&collision);
        PositionalCorrection(&collision);
      }
    }
  }

  UpdateOtherComponents(coordinator);
}

CollisionSystem::CollisionSystem() : keyboard_(nullptr) {}

void CollisionSystem::SetKeyboardInterface(const KeyboardInterface* ptr) {
  keyboard_ = ptr;
}

void CollisionSystem::SetConnector(Connector* ptr) {
  connector_ = ptr;
}
