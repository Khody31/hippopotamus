#include <memory>
#include <set>

#include "game_scene.h"

GameScene::GameScene(std::shared_ptr<Connector> connector) : connector_
                                                                 (std::move(
                                                                     connector)) {
  connector_->SetScene(this);
  timer_id_ = startTimer(game_constants::kTickTime);
  show();
  setFixedSize(1600, 900);
}

void GameScene::timerEvent(QTimerEvent* event) {
  if (event->timerId() != timer_id_) {
    return;
  }
  connector_->OnTick();
}

void GameScene::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  const std::set<Entity>& entities = connector_->GetEntitiesToRender();
  for (auto const& entity : entities) {
    PixmapComponent pixmap_component = connector_->GetPixmapComponent(entity);
    painter.drawPixmap(pixmap_component.upper_left.x(),
                       pixmap_component.upper_left.y(),
                       pixmap_component.lower_right.x() - pixmap_component
                           .upper_left.x(),
                       pixmap_component.lower_right.y() - pixmap_component
                           .upper_left.y(),
                       pixmap_component.pixmap);
  }
}

void GameScene::mousePressEvent(QMouseEvent* event) {
  connector_->MouseClick(WidgetToGameCoordinates(event->pos()));
}
QVector2D GameScene::WidgetToGameCoordinates(const QPoint& widget_coords) {
  return 2 * game_constants::kMaxGameCoordinates * QVector2D(widget_coords)
      / QVector2D(width(), height()) - game_constants::kMaxGameCoordinates;
}
