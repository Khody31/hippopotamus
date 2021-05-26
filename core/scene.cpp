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
  resize(parent->size());
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
  {
    RenderProgressBar(&painter, QVector2D{0.0, 1.2}, 4.0, 0.6, Qt::black, 0);
    RenderProgressBar(&painter, QVector2D{0.0, -1.2}, 4.0, 0.6, Qt::black, 0);
    RenderProgressBar(&painter, QVector2D{1.9, 0.0}, 0.6, 3.0, Qt::black, 0);
    RenderProgressBar(&painter, QVector2D{-1.9, 0.0}, 0.6, 3.0, Qt::black, 0);
  }
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

    float health_percentage = health.value / health.max_health;
    const auto& pixmap =
        coordinator_->GetComponent<PixmapComponent>(entity);
    const auto& transform =
        coordinator_->GetComponent<TransformationComponent>(entity);
    float bar_width;
    float bar_length;
    if (pixmap.size.y() >= 0.5) {
      bar_width = 0.04;
      bar_length = 1.4;
    } else {
      bar_width = 0.015;
      bar_length = 0.3;
    }
    RenderProgressBar(
        painter,
        transform.position + QVector2D{0, pixmap.size.y() * 0.75f},
        bar_length,
        bar_width,
        Qt::black,
        bar_width / 7 * height());
    QColor color;
    if (health_percentage < 0) {
      health_percentage = 0;
    }
    if (health_percentage > 0.5) {
      color = QColor::fromRgb((2.0 - 2 * health_percentage) * 255, 255, 0);
    } else {
      color = QColor::fromRgb(255, 2 * health_percentage * 255, 0);
    }
    RenderProgressBar(
        painter,
        transform.position + QVector2D{0, pixmap.size.y() * 0.75f},
        bar_length,
        bar_width,
        color,
        0,
        health_percentage);
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

  for (auto& entities : entities_by_layers) {
    Coordinator* coordinator_copy = coordinator_;
    sort(entities.begin(), entities.end(),
         [coordinator_copy](Entity lhs, Entity rhs) {
           float lhs_y = coordinator_copy->
               GetComponent<TransformationComponent>(lhs).position.y();
           float rhs_y = coordinator_copy->
               GetComponent<TransformationComponent>(rhs).position.y();
           return lhs_y > rhs_y;
         });
    for (auto const& entity : entities) {
      const auto& pixmap_comp =
          coordinator_->GetComponent<PixmapComponent>(entity);
      const auto& transform_comp =
          coordinator_->GetComponent<TransformationComponent>(entity);
      RenderPixmap(painter,
                   *pixmap_comp.pixmap,
                   transform_comp.position,
                   pixmap_comp.size);
    }
  }
}

void Scene::RenderUserInterface(QPainter* painter) {
  constexpr QVector2D true_width =
      constants::kMaxGameCoordinates / constants::kScreenScalingFactor;
  constexpr float black_strip_midpoint =
      -(constants::kMaxGameCoordinates + true_width).x() / 2;
  {
    const auto& health = coordinator_->GetComponent<HealthComponent>(*player_);
    constexpr float heart_width = 0.15;
    RenderProgressBar(painter,
                      QVector2D{black_strip_midpoint, 0.1f + 2 * heart_width},
                      0.19f,
                      heart_width * 5,
                      Qt::magenta,
                      0,
                      health.value / health.max_health,
                      false);
    static QPixmap heart(":/textures/heart.png");
    for (int32_t i = 0; i < 5; ++i) {
      RenderPixmap(painter,
                   heart,
                   QVector2D{black_strip_midpoint, 0.1f + i * heart_width},
                   QVector2D{0.2f, heart_width});
    }
  }
  {
    const auto& state = coordinator_->GetComponent<StateComponent>(*player_);
    static QPixmap fireball(":/textures/icon-buff-ricochet.png");
    static QPixmap fast_stone(":/textures/icon-buff-damage.png");
    if (state.buff_to_time[BuffType::kFireball] > 0) {
      float progress =
          1.0 * state.buff_to_time[BuffType::kFireball]
              / constants::kMaxBuffTime;
      RenderSector(painter,
                   QVector2D{-black_strip_midpoint, 0.7f},
                   0.1,
                   Qt::magenta,
                   progress);
      RenderSector(painter,
                   QVector2D{-black_strip_midpoint, 0.7f},
                   0.09,
                   Qt::black);
      RenderPixmap(painter,
                   fireball,
                   QVector2D{-black_strip_midpoint, 0.7f},
                   QVector2D{0.16, 0.16});
    } else if (state.buff_to_time[BuffType::kStrongStone] > 0) {
      float progress =
          1.0 * state.buff_to_time[BuffType::kStrongStone]
              / constants::kMaxBuffTime;
      RenderSector(painter,
                   QVector2D{-black_strip_midpoint, 0.7f},
                   0.1,
                   Qt::magenta,
                   progress);
      RenderSector(painter,
                   QVector2D{-black_strip_midpoint, 0.7f},
                   0.09,
                   Qt::black);
      RenderPixmap(painter,
                   fast_stone,
                   QVector2D{-black_strip_midpoint, 0.7f},
                   QVector2D{0.16, 0.16});
    } else {
      return;
    }
  }
}

void Scene::RenderProgressBar(QPainter* painter,
                              const QVector2D& position,
                              float width,
                              float height,
                              const QColor& color,
                              int32_t border_width,
                              float progress,
                              bool is_horizontal) {
  progress = std::min(1.0f, progress);
  progress = std::max(0.0f, progress);
  QVector2D wh_vector = QVector2D{width, height};
  QVector2D ul_corner = position - wh_vector / 2;
  QVector2D lr_corner = position + wh_vector / 2;
  QVector2D delimiter = ul_corner + (lr_corner - ul_corner) * progress;
  QPoint ul_window = utility::GameToWidgetCoord(ul_corner, size());
  QPoint lr_window = utility::GameToWidgetCoord(lr_corner, size());
  QPoint del_window = utility::GameToWidgetCoord(delimiter, size());
  QPoint wh_widget;
  if (is_horizontal) {
    wh_widget = QPoint(del_window.x(), lr_window.y()) - ul_window;
  } else {
    wh_widget = QPoint(lr_window.x(), del_window.y()) - ul_window;
  }
  painter->setPen(color);
  painter->setBrush(color);
  painter->drawRect(ul_window.x() - border_width,
                    ul_window.y() + border_width,
                    wh_widget.x() + 2 * border_width,
                    wh_widget.y() - 2 * border_width);
}

void Scene::RenderPixmap(QPainter* painter,
                         const QPixmap& pixmap,
                         const QVector2D& pos,
                         const QVector2D& pixmap_size) {
  QVector2D inverted_pixmap_size{pixmap_size * QVector2D{1.0, -1.0}};
  QPoint upper_left =
      utility::GameToWidgetCoord(pos - inverted_pixmap_size / 2, size());
  QPoint lower_right =
      utility::GameToWidgetCoord(pos + inverted_pixmap_size / 2, size());
  QRect pixmap_rect = {upper_left, lower_right};
  painter->drawPixmap(pixmap_rect, pixmap);
}

void Scene::RenderSector(QPainter* painter,
                         const QVector2D& pos,
                         float radius,
                         Qt::GlobalColor color,
                         float progress) {
  painter->setPen(color);
  painter->setBrush(color);
  QVector2D ul = pos - QVector2D{radius, radius};
  QVector2D lr = pos + QVector2D{radius, radius};
  QPoint window_ul = utility::GameToWidgetCoord(ul, size());
  QPoint window_lr = utility::GameToWidgetCoord(lr, size());
  QPoint window_wh = window_lr - window_ul;
  painter->drawPie(window_ul.x(),
                   window_ul.y(),
                   window_wh.x(),
                   window_wh.y(),
                   90 * 16,
                   360 * 16 * progress);
}
