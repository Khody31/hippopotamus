#pragma once

#include <QVector2D>

class Connector;

namespace functions {
QPoint GameToWidgetCoord(
    const QVector2D& coord, const QVector2D& scene_size);
QVector2D WidgetToGameCoord(
    const QPoint& coord, const QVector2D& scene_size);
}