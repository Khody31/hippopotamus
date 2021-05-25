#include <QSize>
#include <QVector2D>

#include "transformation.h"
#include "core/connector.h"
#include "core/constants.h"

QPoint utility::GameToWidgetCoord(const QVector2D& coordinates,
                                  const QSize& scene_size,
                                  bool should_scale) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                    static_cast<float>(scene_size.height()));

  QVector2D inverted(coordinates.x(), -coordinates.y());
  if (should_scale) {
    inverted *= constants::kScreenScalingFactor;
  }
  QVector2D result =
      (inverted + constants::kMaxGameCoordinates) * size_vector
          / (2 * constants::kMaxGameCoordinates);
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

QVector2D utility::WidgetToGameCoord(const QPoint& coord,
                                     const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                    static_cast<float>(scene_size.height()));
  QVector2D result =
      QVector2D(coord) * constants::kMaxGameCoordinates * 2
          / size_vector - constants::kMaxGameCoordinates;
  result.setY(-result.y());
  return result / constants::kScreenScalingFactor;
}

double utility::CalculateAngle(QVector2D first_vec, QVector2D second_vec) {
  double scalar_product = first_vec.x() * second_vec.x() + first_vec.y() *
      second_vec.y();
  return scalar_product / (first_vec.length() * second_vec.length());
}

void utility::TurnVector(QVector2D* vec) {
  float x_coordinate = vec->x();
  vec->setX(vec->y());
  vec->setY(-1 * x_coordinate);
}
