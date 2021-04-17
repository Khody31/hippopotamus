#pragma once

#include <QWidget>
#include <QTimerEvent>
#include <memory>

#include "game_constants.h"
#include "core/connector.h"

class GameScene : public QWidget {
  Q_OBJECT
 public:
  explicit GameScene(std::shared_ptr<Connector> connector);

 private:
  void paintEvent(QPaintEvent*) override;
  void timerEvent(QTimerEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

  uint32_t timer_id_;
  std::shared_ptr<Connector> connector_;
};
