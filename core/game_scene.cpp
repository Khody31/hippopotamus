#include "game_scene.h"

GameScene::GameScene(std::shared_ptr<Connector> connector) {
  timer_id_ = startTimer(game_constants::kTickTime);
  connector_ = connector;
  show();
}

void GameScene::timerEvent(QTimerEvent* event) {
  if (event->timerId() != timer_id_) {
    return;
  }
  connector_->OnTick();
  repaint();
}

void GameScene::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  connector_->Render(&painter, width(), height());
}
