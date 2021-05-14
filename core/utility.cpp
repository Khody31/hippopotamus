#include "utility.h"
#include "connector.h"
#include "constants.h"
#include "scene.h"


QPoint utility::GameToWidgetCoord(const QVector2D& coord,
                                  const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                    static_cast<float>(scene_size.height()));

  QVector2D inverted(coord.x(), -coord.y());
  QVector2D result =
      (inverted + game_constants::kMaxGameCoordinates) * size_vector
          / (2 * game_constants::kMaxGameCoordinates);
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

QVector2D utility::WidgetToGameCoord(const QPoint& coord,
                                     const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                   static_cast<float>(scene_size.height()));
  QVector2D result =
      QVector2D(coord) * game_constants::kMaxGameCoordinates * 2
      / size_vector - game_constants::kMaxGameCoordinates;
  result.setY(-result.y());
  return result;
}
