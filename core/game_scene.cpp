#include <memory>
#include <set>
#include <utility>

#include <QKeyEvent>
#include <QPainter>

#include "game_scene.h"
#include "coordinates_helpers.h"

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
    const auto& pixmap_comp =
        connector_->GetPixmapComponent(entity);
    const auto& transform_comp =
        connector_->GetTransformComponent(entity);

    QVector2D inverted_pixmap_size{pixmap_comp.size * QVector2D{1.0, -1.0}};
    QVector2D scene_size = QVector2D(static_cast<float>(width()),
                                     static_cast<float>(height()));
    QPoint upper_left =
        coordinates_helpers::GameToWidgetCoord(
            transform_comp.pos - inverted_pixmap_size / 2, scene_size);
    QPoint lower_right =
        coordinates_helpers::GameToWidgetCoord(
            transform_comp.pos + inverted_pixmap_size / 2, scene_size);

    QRect pixmap_rect = {upper_left, lower_right};
    painter.drawPixmap(pixmap_rect, pixmap_comp.pixmap);
  }
}

void GameScene::keyPressEvent(QKeyEvent* event) {
  connector_->OnKeyPress(static_cast<Qt::Key>(event->key()));
}

void GameScene::keyReleaseEvent(QKeyEvent* event) {
  connector_->OnKeyRelease(static_cast<Qt::Key>(event->key()));
}

void GameScene::mousePressEvent(QMouseEvent* event) {
  connector_->OnMousePress(event);
}
