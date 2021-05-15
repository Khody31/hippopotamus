#include <algorithm>

#include "utility.h"
#include "connector.h"
#include "constants.h"

QPoint utility::GameToWidgetCoord(const QVector2D& coord,
                                  const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                    static_cast<float>(scene_size.height()));

  QVector2D inverted(coord.x(), -coord.y());
  QVector2D result =
      (inverted + constants::kMaxGameCoordinates) * size_vector
          / (2 * constants::kMaxGameCoordinates);
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

QVector2D utility::WidgetToGameCoord(const QPoint& coord,
                                     const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                   static_cast<float>(scene_size.height()));
  QVector2D result =
      QVector2D(coord) * constants::kMaxGameCoordinates * 2
      / size_vector - constants::kMaxGameCoordinates;
  result.setY(-result.y());
  return result;
}

std::pair<float, float> utility::CalculateOverlaps(Collision* collision) {
  CollisionComponent* first = collision->first;
  CollisionComponent* second = collision->second;

  std::array<float, 2> result{};
  for (int i = 0; i < 2; ++i) {
    float first_right = (first->pos + first->size / 2)[i];
    float second_right = (second->pos + second->size / 2)[i];
    float first_left = (first->pos - first->size / 2)[i];
    float second_left = (second->pos - second->size / 2)[i];
    result[i] =
        std::min(first_right, second_right) - std::max(first_left, second_left);
  }
  return {result[0], result[1]};
}

bool utility::IsCollisionPresent(Collision* collision) {
  auto[x_overlap, y_overlap] = CalculateOverlaps(collision);
  QVector2D first_to_second = collision->second->pos - collision->first->pos;

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

void utility::ResolveCollision(Collision* collision) {
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
void utility::PositionalCorrection(Collision* collision) {
  CollisionComponent* first = collision->first;
  CollisionComponent* second = collision->second;

  QVector2D correction = std::max(
      collision->penetration - constants::kCorrectionSlop, 0.0f)
      / (first->inverted_mass + second->inverted_mass)
      * constants::kCorrectionPercent * collision->normal;

  first->pos -= first->inverted_mass * correction;
  second->pos += second->inverted_mass * correction;
}


double utility::CalculateAngle(QVector2D first_vec, QVector2D second_vec) {
  double scalar_product = first_vec.x() * second_vec.x() + first_vec.y() *
      second_vec.y();
  return scalar_product / (first_vec.length() * second_vec.length());
}

void utility::TurnVector(QVector2D* vec) {
  float x_coordinate = vec->x();
  vec->setX(vec->y());
  vec->setY(-1 * x_coordinate);
}
