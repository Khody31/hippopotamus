#include <QPainter>
#include <QWidget>

#include "render_system.h"
#include "game_constants.h"
#include <iostream>
void RenderSystem::Update(Coordinator* game_coordinator) {
  for (auto const& entity : entities_) {
    auto& pixmap_comp = game_coordinator->GetComponent<PixmapComponent>
        (entity);
    auto& tr_comp = game_coordinator->GetComponent<TransformationComponent>
        (entity);
    QVector2D
        upper_left{tr_comp.pos_ - pixmap_comp.size_ / 2};
    QVector2D
        lower_right{tr_comp.pos_ + pixmap_comp.size_ / 2};
    pixmap_comp.game_ul_ = GameToWidgetCoordinates(upper_left, scene_->width
        (), scene_->height());
    pixmap_comp.game_lr_ = GameToWidgetCoordinates(lower_right,
                                                   scene_->width(),
                                                   scene_->height());
  }
}

QPoint RenderSystem::GameToWidgetCoordinates(const QVector2D& coord,
                                             int width,
                                             int height) {
  QVector2D widget_dims{static_cast<float>(width),
                        static_cast<float>(height)};
  QVector2D result{(coord + game_constants::kMaxGameCoordinates) /
      (2 * game_constants::kMaxGameCoordinates) * widget_dims};
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

void RenderSystem::SetScene(QWidget* scene) {
  scene_ = scene;
}

const std::set<Entity>& RenderSystem::GetEntities() {
  return entities_;
}
