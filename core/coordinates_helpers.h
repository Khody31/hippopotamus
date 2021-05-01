#pragma once

#include <QVector2D>

namespace coordinates_helpers {

QPoint GameToWidgetCoord(const QVector2D& coord,const QVector2D& scene_size);

QVector2D WidgetToGameCoord(const QPoint& coord, const QVector2D& scene_size);

}  // namespace coordinates_helpers
