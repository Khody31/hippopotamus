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

  void RenderHealthBars(QPainter* painter);
  void RenderPixmaps(QPainter* painter);

  int32_t timer_id_;
  Connector* connector_;
  Coordinator* coordinator_;
  AbstractController* controller_;
  Entity* player_;
};
