#pragma once

#include <utility>
#include <QVector2D>

#include "components/components.h"

namespace utility {

struct Collision {
  CollisionComponent* first = nullptr;
  CollisionComponent* second = nullptr;
  float penetration = 0;
  QVector2D normal;
};

std::pair<float, float> CalculateOverlaps(Collision* collision);

bool IsCollisionPresent(Collision* collision);

void ResolveCollision(Collision* collision);

void PositionalCorrection(Collision* collision);

}  // namespace utility
