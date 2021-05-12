#pragma once

#include "connector.h"
#include <QVector2D>

namespace helpers {

QPoint GameToWidgetCoord(const QVector2D& coord, const QSize& scene_size);
QVector2D WidgetToGameCoord(const QPoint& coord, const QSize& scene_size);

struct Collision {
  CollisionComponent* fst_collider;
  CollisionComponent* scd_collider;
  float penetration;
  QVector2D normal;
};

std::pair<float, float> CalculateOverlaps(Collision* collision);
bool IsCollisionPresent(Collision* collision);
void ResolveCollision(Collision* collision);
void PositionalCorrection(Collision* collision);

double AngleBetweenVecsCosine(QVector2D first_vec, QVector2D second_vec);
void TurnVector90Degrees(QVector2D& vec);

}  // namespace helpers
