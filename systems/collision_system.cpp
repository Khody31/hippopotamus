#include "collision_system.h"

#include <algorithm>

#include <QVector2D>

struct Collision {
  CollisionComponent* first_collider;
  CollisionComponent* second_collider;
  float penetration;
  QVector2D normal;
};

bool IsCollisionExists(Collision* m) {
  CollisionComponent* first_collider = m->first_collider;
  CollisionComponent* second_collider = m->second_collider;

  QVector2D n = second_collider->upper_left - first_collider->upper_left;
  n.normalize();

  float a_extent =
      (first_collider->upper_left.x() - first_collider->lower_right.x()) / 2;
  float b_extent =
      (second_collider->upper_left.x() - second_collider->lower_right.x()) / 2;

  float x_overlap = a_extent + b_extent - abs(n.x());

  if (x_overlap > 0) {
    a_extent = (first_collider->upper_left.x() -
        first_collider->lower_right.x()) / 2;
    b_extent = (second_collider->upper_left.x() -
        second_collider->lower_right.x()) / 2;

    float y_overlap = a_extent + b_extent - abs(n.y());

    if (y_overlap > 0) {
      if (x_overlap > y_overlap) {
        if (n.x() < 0) {
          m->normal = QVector2D(-1, 0);
        } else {
          m->normal = QVector2D(0, 0);
        }
        m->penetration = x_overlap;
        return true;
      } else {
        if (n.y() < 0) {
          m->normal = QVector2D(0, -1);
        } else {
          m->normal = QVector2D(0, 1);
        }
        m->penetration = y_overlap;
        return true;
      }
    }
  }
  return false;
}

void ResolveCollision(Collision* collision) {
  CollisionComponent* A = collision->first_collider;
  CollisionComponent* B = collision->second_collider;
  QVector2D normal = collision->normal;

  QVector2D relative_velocity = B->velocity - A->velocity;

  float velocity_along_normal = relative_velocity.x() * normal.x() +
      relative_velocity.y() * normal.y();

  if (velocity_along_normal > 0) {
    return;
  }

  float restitution = std::min(A->restitution, B->restitution);
  float j = -(1 + restitution) * velocity_along_normal;
  j /= A->inv_mass + B->inv_mass;

  QVector2D impulse = j * normal;
  A->velocity -= A->inv_mass * impulse;
  B->velocity += B->inv_mass * impulse;
}

void PositionalCorrection(Collision* collision) {
  const float percent = 0.1;
  const float slop = 0.01;

  CollisionComponent* A = collision->first_collider;
  CollisionComponent* B = collision->second_collider;

  QVector2D correction = std::max(
      collision->penetration - slop, 0.0f) / (A->inv_mass + B->inv_mass)
      * percent * collision->normal;

  A->upper_left -= A->inv_mass * correction;
  A->lower_right -= A->inv_mass * correction;
  B->upper_left += B->inv_mass * correction;
  B->upper_left += B->inv_mass * correction;
}

#include <iostream>
void CollisionSystem::Update(Coordinator* coordinator) {
  for (auto entity : entities_) {
    auto& transformation_component =
        coordinator->GetComponent<TransformationComponent>(entity);
    auto& collision_component =
        coordinator->GetComponent<CollisionComponent>(entity);

    collision_component.velocity = transformation_component.velocity;
    float size =
        collision_component.upper_left.x() -
            collision_component.lower_right.x();
    collision_component.upper_left =
        transformation_component.pos + QVector2D(size / 2, size / 2);
    collision_component.lower_right =
        transformation_component.pos - QVector2D(size / 2, size / 2);
  }

  for (auto fst_entity : entities_) {
    for (auto scd_entity : entities_) {
      Collision collision{
          &coordinator->GetComponent<CollisionComponent>(fst_entity),
          &coordinator->GetComponent<CollisionComponent>(scd_entity),
          0,
          {0, 0}
      };

      if (IsCollisionExists(&collision)) {
        ResolveCollision(&collision);
        PositionalCorrection(&collision);
      }
    }
  }

  for (auto entity : entities_) {
    auto& transformation_component =
        coordinator->GetComponent<TransformationComponent>(entity);
    auto& collision_component =
        coordinator->GetComponent<CollisionComponent>(entity);

    collision_component.velocity = transformation_component.velocity;
    float size =
        collision_component.upper_left.x() -
            collision_component.lower_right.x();
    transformation_component.pos =
        collision_component.upper_left - QVector2D(size / 2, size / 2);
    transformation_component.velocity = collision_component.velocity;
  }
}
