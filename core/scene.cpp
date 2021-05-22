#include "scene.h"

#include <QKeyEvent>
#include <QPainter>
#include <algorithm>

#include "utilities/transformation.h"
#include "constants.h"
#include "connector.h"

Scene::Scene(Connector* connector,
             Coordinator* coordinator,
             AbstractController* controller,
             QWidget* parent,
             Entity* player)
    : QWidget(parent),
      coordinator_(coordinator),
      controller_(controller),
      connector_(connector),
      timer_id_(startTimer(constants::kTickTime)),
      player_(player) {
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
  RenderPixmaps(&painter);
  RenderHealthBars(&painter);
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
  controller_->OpenLosingWidget();
  controller_->StopGame();
}

void Scene::OnWin() {
  controller_->OpenWinningWidget();
  controller_->StopGame();
}

void Scene::RenderHealthBars(QPainter* painter) {
  for (Entity entity : connector_->GetEntitiesToRender()) {
    if (!coordinator_->HasComponent<HealthComponent>(entity)
        || entity == *player_) {
      continue;
    }
    const auto& health =
        coordinator_->GetComponent<HealthComponent>(entity);
    if (health.max_health == health.value) {
      continue;
    }
    const auto& pixmap =
        coordinator_->GetComponent<PixmapComponent>(entity);
    const auto& transform =
        coordinator_->GetComponent<TransformationComponent>(entity);
    QVector2D lower_right =
        transform.position + pixmap.size * 0.75 - QVector2D{0, 0.015};
    QVector2D upper_left =
        transform.position + pixmap.size.x() * QVector2D{-0.75, 0.75};
    QVector2D delimiter = {upper_left.x() + (lower_right.x() - upper_left.x())
        * (health.value / health.max_health), 0};
    delimiter.setX(std::max(delimiter.x(), upper_left.x()));
    QPoint window_ul = utility::GameToWidgetCoord(upper_left, size());
    QPoint window_del = utility::GameToWidgetCoord(delimiter, size());
    QPoint window_lr = utility::GameToWidgetCoord(lower_right, size());
    painter->fillRect(window_ul.x() - 1,
                      window_ul.y() - 1,
                      window_lr.x() - window_ul.x() + 2,
                      window_lr.y() - window_ul.y() + 2,
                      Qt::black);
    painter->fillRect(window_ul.x(),
                      window_ul.y(),
                      window_del.x() - window_ul.x(),
                      window_lr.y() - window_ul.y(),
                      Qt::darkGreen);
  }
}

void Scene::RenderPixmaps(QPainter* painter) {
  std::vector<std::vector<Entity>> entities_by_layers(constants::kLayersCount);
  for (auto entity : connector_->GetEntitiesToRender()) {

    const auto& pixmap_comp =
        coordinator_->GetComponent<PixmapComponent>(entity);
    entities_by_layers[pixmap_comp.layer].push_back(entity);
  }

  for (const auto& entities : entities_by_layers) {
    for (auto const& entity : entities) {
      const auto& pixmap_comp =
          coordinator_->GetComponent<PixmapComponent>(entity);
      if (!pixmap_comp.pixmap) {
        continue;
      }
      const auto& transform_comp =
          coordinator_->GetComponent<TransformationComponent>(entity);

      QVector2D inverted_pixmap_size{pixmap_comp.size * QVector2D{1.0, -1.0}};
      QPoint upper_left =
          utility::GameToWidgetCoord(
              transform_comp.position - inverted_pixmap_size / 2, size());
      QPoint lower_right =
          utility::GameToWidgetCoord(
              transform_comp.position + inverted_pixmap_size / 2, size());
      QRect pixmap_rect = {upper_left, lower_right};
      painter->drawPixmap(pixmap_rect, *pixmap_comp.pixmap);
    }
  }
}
