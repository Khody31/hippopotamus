#include <QPainter>

#include "render_system.h"
#include "game_constants.h"

void RenderSystem::Update(Coordinator* game_coordinator) {
  for (auto const& entity : entities_) {
    auto& pixmap_comp = game_coordinator->GetComponent<PixmapComponent>
        (entity);
    auto& tr_comp = game_coordinator->GetComponent<TransformationComponent>
        (entity);
    // pixmap_comp.поле->DoSomething();
  }
}

void RenderSystem::Render (Coordinator* game_coordinator, QPainter* painter, int width, int height) {
  for (auto const& entity : entities_) {
    auto& pixmap_comp = game_coordinator->GetComponent<PixmapComponent>
        (entity);
    auto& tr_comp = game_coordinator->GetComponent<TransformationComponent>
        (entity);
    QVector2D
        upper_left{tr_comp.pos_ - pixmap_comp.size_ / 2};
    QVector2D
        lower_right{tr_comp.pos_ + pixmap_comp.size_ / 2};
    QPoint
        game_ul{GameToWidgetCoordinates(upper_left, width, height)};
    QPoint
        game_lr{GameToWidgetCoordinates(lower_right, width, height)};
    painter->drawPixmap(game_ul.x(),
                       game_ul.y(),
                       game_lr.x() - game_ul.x(),
                       game_lr.y() - game_ul.y(),
                       pixmap_comp.pixmap_);
  }
}

QVector2D RenderSystem::WidgetToGameCoordinates(const QPoint& coord, int
width, int height) {
  QVector2D widget_dims{static_cast<float>(width),
                        static_cast<float>(height)};
  return QVector2D(coord) / widget_dims * 2 *
  game_constants::kMaxGameCoordinates
      - game_constants::kMaxGameCoordinates;
}

QPoint RenderSystem::GameToWidgetCoordinates(const QVector2D& coord, int width, int height) {
  QVector2D widget_dims{static_cast<float>(width),
                        static_cast<float>(height)};
  QVector2D result{(coord + game_constants::kMaxGameCoordinates) /
      (2 * game_constants::kMaxGameCoordinates) * widget_dims};
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}