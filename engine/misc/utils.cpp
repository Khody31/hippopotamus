#include "engine/misc/utils.h"
#include "engine/system/game_widget.h"
#include "constants.h"

namespace utils {

QVector2D WidgetToGameCoordinates(const QPoint& coord) {
  QVector2D widget_dims{static_cast<float>(GameWidget::Get().width()),
                        static_cast<float>(GameWidget::Get().height())};
  return QVector2D(coord) / widget_dims * 2 * constants::kMaxGameCoordinates
      - constants::kMaxGameCoordinates;
}

QPoint GameToWidgetCoordinates(const QVector2D& coord) {
  QVector2D widget_dims{static_cast<float>(GameWidget::Get().width()),
                        static_cast<float>(GameWidget::Get().height())};
  QVector2D result{(coord + constants::kMaxGameCoordinates) /
      (2 * constants::kMaxGameCoordinates) * widget_dims};
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

}  // namespace utils
