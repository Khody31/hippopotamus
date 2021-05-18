#pragma once

#include <memory>

#include <QWidget>
#include <QTimerEvent>

#include "view/abstract_controller.h"

class Connector;

class Scene : public QWidget {
  Q_OBJECT
 public:
  explicit Scene(Connector* connector,
                 AbstractController* controller,
                 QWidget* parent);

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

  int32_t timer_id_;
  Connector* connector_;
  AbstractController* controller_;
};
