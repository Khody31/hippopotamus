#include "scene.h"

#include <QKeyEvent>
#include <QPainter>
#include <algorithm>
#include <vector>

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
  painter.fillRect(0, 0, width(), height(), Qt::black);
  RenderPixmaps(&painter);
  RenderHealthBars(&painter);
  RenderUserInterface(&painter);
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

    float health_percentage = health.value / health.max_health;
    RenderProgressBar(
        painter, transform.position + QVector2D{0, pixmap.size.y() * 0.75f},
        pixmap.size.x() * 1.5f, 0.015, Qt::black, 1);
    RenderProgressBar(
        painter, transform.position + QVector2D{0, pixmap.size.y() * 0.75f},
        pixmap.size.x() * 1.5f, 0.015, Qt::darkGreen, 0, health_percentage);
  }
}

void Scene::RenderPixmaps(QPainter* painter) {
  std::vector<std::vector<Entity>> entities_by_layers(
      static_cast<int32_t>(SceneLayers::kEnumSize));

  for (auto entity : connector_->GetEntitiesToRender()) {
    const auto& pixmap_component =
        coordinator_->GetComponent<PixmapComponent>(entity);
    if (!pixmap_component.pixmap) {
      continue;
    }

    auto layer = static_cast<int32_t>(pixmap_component.layer);
    entities_by_layers[layer].push_back(entity);
  }

  for (const auto& entities : entities_by_layers) {
    for (auto const& entity : entities) {
      const auto& pixmap_comp =
          coordinator_->GetComponent<PixmapComponent>(entity);
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

void Scene::RenderUserInterface(QPainter* painter) {
  const QVector2D interface_pos = QVector2D{-1.0f, 0.5f};
  const QVector2D interface_dims = QVector2D{0.6f, 0.25f};
  {
    // RenderProgressBar(painter,
    // interface_pos,
    // interface_dims.x(),
    // interface_dims.y(),
    // Qt::black,
    // 0);
  }
  {
    const auto& health = coordinator_->GetComponent<HealthComponent>(*player_);
    RenderProgressBar(painter,
                      interface_pos + QVector2D{0.0f, 0.07f},
                      0.5,
                      0.03,
                      Qt::darkRed,
                      2);
    RenderProgressBar(painter,
                      interface_pos + QVector2D{0.0f, 0.07f},
                      0.5,
                      0.03,
                      Qt::red,
                      0,
                      health.value / health.max_health);
  }
  {
    const auto& state = coordinator_->GetComponent<StateComponent>(*player_);
    float buff_duration = constants::kMaxBuffTime;
    float buff_remaining = std::max(state.buff_to_time[BuffType::kFireball],
                                    state.buff_to_time[BuffType::kStrongStone]);
    if (buff_remaining > 0) {
      RenderProgressBar(painter,
                        interface_pos + QVector2D{0.0f, 0.03f},
                        0.5,
                        0.015,
                        Qt::darkYellow,
                        2);
      RenderProgressBar(painter,
                        interface_pos + QVector2D{0.0f, 0.03f},
                        0.5,
                        0.015,
                        Qt::yellow,
                        0,
                        buff_remaining / buff_duration);
    }
  }
  {
    // QVector2D inverted_pixmap_size{QVector2D{0.2, 0.2} * QVector2D{ 1.0, -1.0 }};
    // QPoint upper_left =
    //     utility::GameToWidgetCoord(
    //         interface_pos - QVector2D{0.2, 0.0} - inverted_pixmap_size / 2,
    //         size());
    // QPoint lower_right =
    //     utility::GameToWidgetCoord(
    //         interface_pos - QVector2D{0.2, 0.0} + inverted_pixmap_size / 2,
    //         size());
    // QRect pixmap_rect = {upper_left, lower_right};
    // painter->drawPixmap(pixmap_rect, QPixmap(":/textures/player.png"));
  }
}

void Scene::RenderProgressBar(QPainter* painter,
                              const QVector2D& position,
                              float width,
                              float height,
                              Qt::GlobalColor color,
                              int32_t border_width,
                              float progress) {
  progress = std::min(1.0f, progress);
  progress = std::max(0.0f, progress);
  QVector2D wh_vector = QVector2D{width, height};
  QVector2D ul_corner = position - wh_vector / 2;
  QVector2D lr_corner = position + wh_vector / 2;
  QVector2D delimiter = ul_corner + (lr_corner - ul_corner) * progress;
  QPoint ul_window = utility::GameToWidgetCoord(ul_corner, size());
  QPoint lr_window = utility::GameToWidgetCoord(lr_corner, size());
  QPoint del_window = utility::GameToWidgetCoord(delimiter, size());
  QPoint wh_widget = QPoint{del_window.x(), lr_window.y()} - ul_window;
  painter->fillRect(ul_window.x() - border_width,
                    ul_window.y() + border_width,
                    wh_widget.x() + 2 * border_width,
                    wh_widget.y() - 2 * border_width,
                    color);

}
