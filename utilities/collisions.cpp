#include "collisions.h"

#include <array>
#include <algorithm>

#include "core/constants.h"

namespace utility {

std::pair<float, float> CalculateOverlaps(Collision* collision) {
  CollisionComponent* first = collision->first;
  CollisionComponent* second = collision->second;

  std::array<float, 2> result{};
  for (int i = 0; i < 2; ++i) {
    float first_right = (first->position + first->size / 2)[i];
    float second_right = (second->position + second->size / 2)[i];
    float first_left = (first->position - first->size / 2)[i];
    float second_left = (second->position - second->size / 2)[i];
    result[i] =
        std::min(first_right, second_right) - std::max(first_left, second_left);
  }
  return {result[0], result[1]};
}

// To just get info about if collision is present, it is enough to
// set only position and size of items you check.
bool IsCollisionPresent(Collision* collision) {
  auto[x_overlap, y_overlap] = CalculateOverlaps(collision);
  QVector2D first_to_second =
      collision->second->position - collision->first->position;

  if (!(x_overlap > 0 && y_overlap > 0)) {
    return false;
  }

  if (x_overlap < y_overlap) {
    if (first_to_second.x() < 0) {
      collision->normal = QVector2D(-1, 0);
    } else {
      collision->normal = QVector2D(1, 0);
    }
    collision->penetration = x_overlap;
    return true;
  }

  if (first_to_second.y() < 0) {
    collision->normal = QVector2D(0, -1);
  } else {
    collision->normal = QVector2D(0, 1);
  }
  collision->penetration = y_overlap;
  return true;
}

void ResolveCollision(Collision* collision) {
  CollisionComponent* first = collision->first;
  CollisionComponent* second = collision->second;
  QVector2D normal = collision->normal;

  QVector2D relative_velocity = second->velocity - first->velocity;
  float velocity_along_normal = relative_velocity.x() * normal.x() +
      relative_velocity.y() * normal.y();

  // we don't solve the collision if it will be solved itself
  if (velocity_along_normal > 0) {
    return;
  }

  float elasticity = std::min(first->elasticity, second->elasticity);
  float impulse_module = -velocity_along_normal * (1 + elasticity);
  impulse_module /= first->inverted_mass + second->inverted_mass;

  QVector2D impulse = impulse_module * normal;
  first->velocity -= first->inverted_mass * impulse;
  second->velocity += second->inverted_mass * impulse;
}

// needed to solve problem with drowning colliders
void PositionalCorrection(Collision* collision) {
  CollisionComponent* first = collision->first;
  CollisionComponent* second = collision->second;

  QVector2D correction = std::max(
      collision->penetration - constants::kCorrectionSlope, 0.0f)
      / (first->inverted_mass + second->inverted_mass)
      * constants::kCorrectionPercent * collision->normal;

  first->position -= first->inverted_mass * correction;
  second->position += second->inverted_mass * correction;
}

}  // namespace utility
