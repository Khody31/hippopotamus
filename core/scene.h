#pragma once

#include <memory>

#include <QWidget>
#include <QTimerEvent>

#include "engine/coordinator.h"
#include "engine/types.h"
#include "view/abstract_controller.h"

class Connector;

class Scene : public QWidget {
  Q_OBJECT

 public:
  explicit Scene(Connector* connector,
                 Coordinator* coordinator,
                 AbstractController* controller,
                 QWidget* parent,
                 Entity* player);

  void StartTimer();
  void StopTimer();

  void OnLoss();
  void OnWin();

 private:
  void paintEvent(QPaintEvent*) override;
  void timerEvent(QTimerEvent*) override;

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void mousePressEvent(QMouseEvent*) override;

  void RenderHealthBars(QPainter*);
  void RenderPixmaps(QPainter*);
  void RenderProgressBar(QPainter*,
                         const QVector2D& pos,
                         float width,
                         float height,
                         const QColor&,
                         int32_t border_width,
                         float progress = 1.0,
                         bool is_horizontal = true);
  void RenderSector(QPainter*,
                    const QVector2D& pos,
                    float radius,
                    Qt::GlobalColor,
                    float progress = 1.0);
  void RenderPixmap(QPainter*,
                    const QPixmap&,
                    const QVector2D& pos,
                    const QVector2D& pixmap_size);
  void RenderUserInterface(QPainter* painter);

  int32_t timer_id_;
  Connector* connector_;
  Coordinator* coordinator_;
  AbstractController* controller_;
  Entity* player_;
};
