#ifndef ENGINE_UTILS_H_
#define ENGINE_UTILS_H_


namespace utils {

QVector2D WidgetToGameCoordinates(const QPoint& coord);

QPoint GameToWidgetCoordinates(const QVector2D& coord);

}  // namespace utils

#endif  // ENGINE_UTILS_H_
