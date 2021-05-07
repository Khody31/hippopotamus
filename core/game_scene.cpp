#include <memory>
#include <set>
#include <QKeyEvent>
#include <utility>
#include <QPainter>

#include "game_scene.h"
#include "helpers.h"

GameScene::GameScene(std::shared_ptr<Connector> connector,
                     std::shared_ptr<AbstractController> controller, QWidget* parent)
    : connector_(std::move(connector)), controller_(std::move(controller)),
      QWidget(parent) {
  timer_id_ = startTimer(game_constants::kTickTime);
  connector_->SetScene(this);
  show();
  resize(1600, 900);
  setFocus();
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
    const auto& pixmap_comp =
        connector_->GetPixmapComponent(entity);
    const auto& transform_comp =
        connector_->GetTransformComponent(entity);

    QVector2D inverted_pixmap_size{pixmap_comp.size * QVector2D{1.0, -1.0}};
    QPoint upper_left =
        helpers::GameToWidgetCoord(
            transform_comp.pos - inverted_pixmap_size / 2, size());
    QPoint lower_right =
        helpers::GameToWidgetCoord(
            transform_comp.pos + inverted_pixmap_size / 2, size());

    QRect pixmap_rect = {upper_left, lower_right};
    painter.drawPixmap(pixmap_rect, pixmap_comp.pixmap);
  }
}

void GameScene::keyPressEvent(QKeyEvent* event) {
  // ignore event for it to be propagated to parent widget (i.e. Game Widget)
  if (event->key() == Qt::Key_Escape) {
    QWidget::keyPressEvent(event);
  }
  connector_->OnKeyPress(static_cast<Qt::Key>(event->key()));
  if (event->key() == Qt::Key_0) {
    OnLoss();
  }
}

void GameScene::keyReleaseEvent(QKeyEvent* event) {
  connector_->OnKeyRelease(static_cast<Qt::Key>(event->key()));
}

void GameScene::mousePressEvent(QMouseEvent* event) {
  connector_->OnMousePress(event);
}

void GameScene::StartTimer() {
  timer_id_ = startTimer(game_constants::kTickTime);
}

void GameScene::StopTimer() {
  killTimer(timer_id_);
}

void GameScene::OnLoss() {
  controller_->StopGame();
  controller_->OpenWinningWidget();
}

void GameScene::OnWin() {
  controller_->StopGame();
  controller_->OpenWinningWidget();
}
