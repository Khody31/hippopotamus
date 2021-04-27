#include <memory>
#include <set>
#include <QKeyEvent>
#include <utility>

#include "game_scene.h"
#include "functions.h"

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
  for (auto const& entity : connector_->render_system_->GetEntities()) {
    const auto& pixmap_comp =
        connector_->coordinator_.GetComponent<PixmapComponent>(entity);
    const auto& tr_comp =
        connector_->coordinator_.GetComponent<TransformationComponent>(entity);
    QVector2D inverted_size{pixmap_comp.size * QVector2D{1.0, -1.0}};
    QPoint upper_left =
        Functions::GameToWidgetCoord(tr_comp.pos - inverted_size / 2);
    QPoint lower_right =
        Functions::GameToWidgetCoord(tr_comp.pos + inverted_size / 2);

    painter.drawPixmap(upper_left.x(),
                       upper_left.y(),
                       lower_right.x() - upper_left.x(),
                       lower_right.y() - upper_left.y(),
                       pixmap_comp.pixmap);
  }
}

void GameScene::keyPressEvent(QKeyEvent* event) {
  connector_->OnKeyPress(static_cast<Qt::Key>(event->key()));
}

void GameScene::keyReleaseEvent(QKeyEvent* event) {
  connector_->OnKeyRelease(static_cast<Qt::Key>(event->key()));
}

void GameScene::mousePressEvent(QMouseEvent* event) {
  connector_->OnMousePress(event->button());
}
