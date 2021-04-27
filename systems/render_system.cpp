#include <QPainter>
#include <QWidget>
#include <unordered_set>

#include "render_system.h"
#include "core/game_constants.h"

void RenderSystem::Update(Coordinator* game_coordinator) {
  for (const auto& entity : entities_) {
    auto& pixmap_comp = game_coordinator->GetComponent<PixmapComponent>
        (entity);
    auto& tr_comp = game_coordinator->GetComponent<TransformationComponent>
        (entity);
    QVector2D inverted_size{pixmap_comp.size * QVector2D{1.0, -1.0}};
    QVector2D upper_left{tr_comp.pos - inverted_size / 2};
    QVector2D lower_right{tr_comp.pos + inverted_size / 2};
    pixmap_comp.upper_left = GameToWidgetCoordinates(upper_left);
    pixmap_comp.lower_right = GameToWidgetCoordinates(lower_right);
  }
  scene_->repaint();
}

QPoint RenderSystem::GameToWidgetCoordinates(const QVector2D& coord) {
  QVector2D widget_dims{static_cast<float>(scene_->width()),
                        static_cast<float>(scene_->height())};
  QVector2D inverted{coord.x(), -coord.y()};
  QVector2D result{(inverted + game_constants::kMaxGameCoordinates)
                       / (2 * game_constants::kMaxGameCoordinates)
                       * widget_dims};
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

void RenderSystem::SetScene(QWidget* scene) {
  scene_ = scene;
}

const std::unordered_set<Entity>& RenderSystem::GetEntities() {
  return entities_;
}

RenderSystem::RenderSystem() : scene_(nullptr) {}
