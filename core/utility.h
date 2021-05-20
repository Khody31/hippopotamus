#pragma once

#include <QVector2D>
#include <components/components.h>
#include <utility>

namespace utility {

struct Collision {
  CollisionComponent* first = nullptr;
  CollisionComponent* second = nullptr;
  float penetration = 0;
  QVector2D normal;
};

QPoint GameToWidgetCoord(const QVector2D& coord, const QSize& scene_size);

QVector2D WidgetToGameCoord(const QPoint& coord, const QSize& scene_size);

std::pair<float, float> CalculateOverlaps(Collision* collision);

bool IsCollisionPresent(Collision* collision);

void ResolveCollision(Collision* collision);

void PositionalCorrection(Collision* collision);

double CalculateAngle(QVector2D first_vec, QVector2D second_vec);

// turned vector per 90 degrees
void TurnVector(QVector2D* vec);

QString GetRoomPath(int32_t id);

}  // namespace utility
