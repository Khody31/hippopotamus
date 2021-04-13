#include "game_scene.h"

GameScene::GameScene(std::shared_ptr<Connector> connector) : connector_
(std::move(connector)) {
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
  repaint();
}
#include <iostream>
#include <utility>
void GameScene::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  std::set<Entity> entities = connector_->GetEntitiesToRender();
  for (auto const& entity : entities) {
    PixmapComponent pixmap_component = connector_->GetPixmapComponent(entity);
    painter.drawPixmap(pixmap_component.game_ul.x(),
                       pixmap_component.game_ul.y(),
                       pixmap_component.game_lr.x() - pixmap_component
                           .game_ul.x(),
                       pixmap_component.game_lr.y() - pixmap_component
                           .game_ul.y(),
                       pixmap_component.pixmap);
  }
}
