#pragma once

#include <QWidget>
#include <QTimerEvent>
#include <memory>

#include "constants.h"
#include "core/connector.h"

class Scene : public QWidget {
  Q_OBJECT
 public:
  explicit Scene(Connector* connector, QWidget* parent);

  void StartTimer();
  void StopTimer();

 private:
  void paintEvent(QPaintEvent*) override;
  void timerEvent(QTimerEvent*) override;

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void mousePressEvent(QMouseEvent*) override;

  uint32_t timer_id_;
  Connector* connector_;
};
