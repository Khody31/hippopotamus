#include "functions.h"
#include "connector.h"
#include "game_constants.h"
#include "game_scene.h"

QPoint Functions::GameToWidgetCoord(const QVector2D& coord) {
  QVector2D inverted{coord.x(), -coord.y()};
  QVector2D result =
      (inverted + game_constants::kMaxGameCoordinates)
      * connector_->GetSceneSize()
      / (2 * game_constants::kMaxGameCoordinates);
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

QVector2D Functions::WidgetToGameCoord(const QPoint& coord) {
  QVector2D result = QVector2D(coord) * game_constants::kMaxGameCoordinates * 2
      / connector_->GetSceneSize() - game_constants::kMaxGameCoordinates;
  result.setY(-result.y());
  return result;
}

// The needed value is set in Connector's constructor.
Connector* Functions::connector_ = nullptr;
