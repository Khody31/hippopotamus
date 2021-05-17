#include "scene.h"

#include <QKeyEvent>
#include <QPainter>

#include "utility.h"
#include "constants.h"
#include "connector.h"

Scene::Scene(Connector* connector,
             AbstractController* controller,
             QWidget* parent)
    : QWidget(parent),
      controller_(controller),
      connector_(connector),
      timer_id_(startTimer(constants::kTickTime)) {
  show();
  resize(1600, 900);
  setFocus();
}

void Scene::timerEvent(QTimerEvent* event) {
  if (event->timerId() != timer_id_) {
    return;
  }
  connector_->OnTick();
}

void Scene::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  for (auto const& entity : connector_->GetEntitiesToRender()) {
    const auto& pixmap_comp =
        connector_->GetPixmapComponent(entity);
    if (pixmap_comp.pixmap == nullptr) {
      continue;
    }
    const auto& transform_comp =
        connector_->GetTransformComponent(entity);

    QVector2D inverted_pixmap_size{pixmap_comp.size * QVector2D{1.0, -1.0}};
    QPoint upper_left =
        utility::GameToWidgetCoord(
            transform_comp.pos - inverted_pixmap_size / 2, size());
    QPoint lower_right =
        utility::GameToWidgetCoord(
            transform_comp.pos + inverted_pixmap_size / 2, size());

    QRect pixmap_rect = {upper_left, lower_right};
    painter.drawPixmap(pixmap_rect, *pixmap_comp.pixmap);
  }
}

void Scene::keyPressEvent(QKeyEvent* event) {
  // ignore event for it to be propagated to parent widget (Game CustomWidget)
  if (event->key() == Qt::Key_Escape) {
    QWidget::keyPressEvent(event);
  }
  connector_->OnKeyPress(static_cast<Qt::Key>(event->key()));
}

void Scene::keyReleaseEvent(QKeyEvent* event) {
  connector_->OnKeyRelease(static_cast<Qt::Key>(event->key()));
}

void Scene::mousePressEvent(QMouseEvent* event) {
  connector_->OnMousePress(event);
}

void Scene::StartTimer() {
  timer_id_ = startTimer(constants::kTickTime);
}

void Scene::StopTimer() {
  killTimer(timer_id_);
}

void Scene::OnLoss() {
  controller_->StopGame();
  controller_->OpenWinningWidget();
}

void Scene::OnWin() {
  controller_->StopGame();
  controller_->OpenWinningWidget();
}
