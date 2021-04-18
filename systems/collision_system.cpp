#include "collision_system.h"
#include "components/components.h"

#include <algorithm>

#include <QVector2D>


#include <QDebug>

struct Collision {
  CollisionComponent* first_collider;
  CollisionComponent* second_collider;
  float penetration;
  QVector2D normal;
};

bool IsCollisionExists(Collision* collision) {
  CollisionComponent* first_collider = collision->first_collider;
  CollisionComponent* second_collider = collision->second_collider;

  QVector2D n = second_collider->upper_left - first_collider->upper_left;

  float first_extent =
      (first_collider->lower_right.x() - first_collider->upper_left.x()) / 2;
  float second_extent =
      (second_collider->lower_right.x() - second_collider->upper_left.x()) / 2;

  float x_overlap = first_extent + second_extent - abs(n.x());

  if (x_overlap > 0) {
    first_extent = (first_collider->upper_left.y() -
        first_collider->lower_right.y()) / 2;
    second_extent = (second_collider->upper_left.y() -
        second_collider->lower_right.y()) / 2;

    float y_overlap = first_extent + second_extent - abs(n.y());

    if (y_overlap > 0) {
      if (x_overlap < y_overlap) {
        if (n.x() < 0) {
          collision->normal = QVector2D(-1, 0);
        } else {
          collision->normal = QVector2D(1, 0);
        }
        collision->penetration = x_overlap;
        return true;
      } else {
        if (n.y() < 0) {
          collision->normal = QVector2D(0, -1);
        } else {
          collision->normal = QVector2D(0, 1);
        }
        collision->penetration = y_overlap;
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

  //qDebug() << normal << ' ' << relative_velocity;
  //qDebug() << velocity_along_normal;
  if (velocity_along_normal > 0) {
   return;
  }


  float restitution = std::min(A->restitution, B->restitution);
  float j = -1 * (1 + restitution) * velocity_along_normal;
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

void CollisionSystem::Update(Coordinator* coordinator) {
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

    if (entity == 2) {
      qDebug() << collision_component.lower_right;
    }

  }

  for (auto fst_entity : entities_) {
    for (auto scd_entity : entities_) {
      if (fst_entity == scd_entity) {
        continue;
      }

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
    auto& motion_component =
        coordinator->GetComponent<MotionComponent>(entity);

    float size_x = collision_component.size.x();
    float size_y = collision_component.upper_left.y() -
        collision_component.lower_right.y();

    transformation_component.pos =
        collision_component.lower_right + QVector2D(-size_x / 2, size_y / 2);

    if (collision_component.velocity != QVector2D(0, 0)) {
      motion_component.speed = collision_component.velocity.length();
    }
    motion_component.direction = collision_component.velocity.normalized();
  }
}
