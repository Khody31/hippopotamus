#pragma  once

namespace utils {

QVector2D WidgetToGameCoordinates(const QPoint& coord);

QPoint GameToWidgetCoordinates(const QVector2D& coord);

}  // namespace utils
