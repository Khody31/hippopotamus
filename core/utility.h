#pragma once

#include <QVector2D>
#include <components/components.h>
#include <utility>

namespace utility {

QPoint GameToWidgetCoord(const QVector2D& coord, const QSize& scene_size);

QVector2D WidgetToGameCoord(const QPoint& coord, const QSize& scene_size);

}  // namespace utility
