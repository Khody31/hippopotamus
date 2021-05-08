#include "helpers.h"

#include "game_constants.h"
#include "game_scene.h"

QPoint helpers::GameToWidgetCoord(const QVector2D& coord,
                                  const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                    static_cast<float>(scene_size.height()));

  QVector2D inverted(coord.x(), -coord.y());
  QVector2D result =
      (inverted + game_constants::kMaxGameCoordinates) * size_vector
          / (2 * game_constants::kMaxGameCoordinates);
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

QVector2D helpers::WidgetToGameCoord(const QPoint& coord,
                                     const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                   static_cast<float>(scene_size.height()));
  QVector2D result =
      QVector2D(coord) * game_constants::kMaxGameCoordinates * 2
      / size_vector - game_constants::kMaxGameCoordinates;
  result.setY(-result.y());
  return result;
}

std::pair<float, float> helpers::CalculateOverlaps(Collision* collision) {
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

bool helpers::IsCollisionPresent(Collision* collision) {
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

void helpers::ResolveCollision(Collision* collision) {
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
void helpers::PositionalCorrection(Collision* collision) {
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
