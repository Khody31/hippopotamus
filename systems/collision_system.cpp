#include "collision_system.h"
#include "components/components.h"

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
  QVector2D from_fst_to_scd = scd_collider->upper_left
      - fst_collider->upper_left;

  std::array<float, 2> result{};
  for (int i = 0; i < 2; ++i) {
    result[i] = fst_collider->size[i] +
        scd_collider->size[i] - 2 * abs(from_fst_to_scd[i]);

    if (scd_collider->lower_right[i] > fst_collider->lower_right[i] &&
        scd_collider->upper_left[i] < fst_collider->upper_left[i]) {
      result[i] = fst_collider->size[i];
    }
    if (fst_collider->lower_right[i] > scd_collider->lower_right[i] &&
        fst_collider->upper_left[i] < scd_collider->upper_left[i]) {
      result[i] = scd_collider->size[i];
    }
  }
  return std::make_pair(result[0], result[1]);
}

bool IsCollisionExists(Collision* collision) {
  auto[x_overlap, y_overlap] = CalculateOverlaps(collision);
  QVector2D from_fst_to_scd = collision->scd_collider->upper_left
      - collision->fst_collider->upper_left;

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
  const float percent = 0.1;
  const float slop = 0.01;

  CollisionComponent* fst_collider = collision->fst_collider;
  CollisionComponent* scd_collider = collision->scd_collider;

  QVector2D correction = std::max(
      collision->penetration - slop, 0.0f) /
      (fst_collider->inverted_mass + scd_collider->inverted_mass)
      * percent * collision->normal;

  fst_collider->upper_left -= fst_collider->inverted_mass * correction;
  fst_collider->lower_right -= fst_collider->inverted_mass * correction;
  scd_collider->upper_left += scd_collider->inverted_mass * correction;
  scd_collider->lower_right += scd_collider->inverted_mass * correction;
}

void CollisionSystem::UpdateCollisionComponents(Coordinator* coordinator) {
  // synchronize collision component's fields with other components
  for (auto entity : entities_) {
    auto& transformation_component =
        coordinator->GetComponent<TransformationComponent>(entity);
    auto& collision_component =
        coordinator->GetComponent<CollisionComponent>(entity);
    auto& motion_component =
        coordinator->GetComponent<MotionComponent>(entity);

    collision_component.velocity =
        motion_component.speed * motion_component.direction;

    float size_x = collision_component.size.x();
    float size_y = collision_component.size.y();

    collision_component.upper_left =
        transformation_component.pos + QVector2D(-size_x / 2, size_y / 2);
    collision_component.lower_right =
        transformation_component.pos + QVector2D(size_x / 2, -size_y / 2);
  }
}

void CollisionSystem::UpdateOtherComponents(Coordinator* coordinator) {
  // synchronize other component's field with collision components
  for (auto entity : entities_) {
    auto& transformation_component =
        coordinator->GetComponent<TransformationComponent>(entity);
    auto& collision_component =
        coordinator->GetComponent<CollisionComponent>(entity);
    auto& motion_component =
        coordinator->GetComponent<MotionComponent>(entity);

    float size_x = collision_component.size.x();
    float size_y = collision_component.size.y();

    transformation_component.pos =
        collision_component.lower_right + QVector2D(-size_x / 2, size_y / 2);

    motion_component.speed = collision_component.velocity.length();
    motion_component.direction = collision_component.velocity.normalized();
  }
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
        ResolveCollision(&collision);
        PositionalCorrection(&collision);
      }
    }
  }

  UpdateOtherComponents(coordinator);
}
