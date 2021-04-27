#include <memory>
#include <set>
#include <QKeyEvent>
#include <utility>

#include "game_scene.h"

GameScene::GameScene(std::shared_ptr<Connector> connector)
    : connector_(std::move(connector)) {
  timer_id_ = startTimer(game_constants::kTickTime);
  connector_->SetScene(this);
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
  for (auto const& entity : connector_->GetEntitiesToRender()) {
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

void GameScene::keyPressEvent(QKeyEvent* event) {
  connector_->OnKeyPress(static_cast<Qt::Key>(event->key()));
}

void GameScene::keyReleaseEvent(QKeyEvent* event) {
  connector_->OnKeyRelease(static_cast<Qt::Key>(event->key()));
}
