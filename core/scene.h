#pragma once

#include <QWidget>
#include <QTimerEvent>
#include <memory>

#include "constants.h"
#include "core/connector.h"
#include "view/abstract_controller.h"

class Scene : public QWidget {
  Q_OBJECT
 public:
  explicit Scene(Connector* connector, AbstractController* controller, QWidget* parent);

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

  uint32_t timer_id_;
  Connector* connector_;
  AbstractController* controller_;
};
