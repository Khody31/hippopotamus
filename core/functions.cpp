#include "functions.h"
#include "connector.h"
#include "game_constants.h"
#include "game_scene.h"

QPoint functions::GameToWidgetCoord(
    const QVector2D& coord, const QVector2D& scene_size) {
  QVector2D inverted{coord.x(), -coord.y()};
  QVector2D result =
      (inverted + game_constants::kMaxGameCoordinates)
      * scene_size
      / (2 * game_constants::kMaxGameCoordinates);
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

QVector2D functions::WidgetToGameCoord(
    const QPoint& coord, const QVector2D& scene_size) {
  QVector2D result = QVector2D(coord) * game_constants::kMaxGameCoordinates * 2
      / scene_size - game_constants::kMaxGameCoordinates;
  result.setY(-result.y());
  return result;
}
