#pragma once

#include <QVector2D>
#include <components/components.h>
#include <utility>

namespace utility {

QPoint GameToWidgetCoord(const QVector2D& coordinates,
                         const QSize& scene_size,
                         bool should_scale = true);
QVector2D WidgetToGameCoord(const QPoint& coord, const QSize& scene_size);

double CalculateAngle(QVector2D first_vec, QVector2D second_vec);

// Turns given vector by 90 degrees
void TurnVector(QVector2D* vec);

}  // namespace utility
