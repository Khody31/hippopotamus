#include "functions.h"
#include "connector.h"
#include "game_constants.h"
#include "game_scene.h"

QPoint Functions::GameToWidgetCoord(const QVector2D& coord) {
  QVector2D widget_dims{static_cast<float>(connector_->scene_->width()),
                        static_cast<float>(connector_->scene_->height())};
  QVector2D inverted{coord.x(), -coord.y()};
  QVector2D result{(inverted + game_constants::kMaxGameCoordinates)
                       / (2 * game_constants::kMaxGameCoordinates)
                       * widget_dims};
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

QVector2D Functions::WidgetToGameCoord(const QPoint& coord) {
  ///TODO NikolaiNick
  return QVector2D{0,0};
}

Connector* Functions::connector_;