#pragma once

#include <QWidget>
#include <QTimerEvent>
#include <memory>

#include "game_constants.h"
#include "core/connector.h"

class GameScene : public QWidget {
  Q_OBJECT
 public:
  explicit GameScene(std::shared_ptr<Connector> connector, QWidget* parent);

  void StartTimer();
  void StopTimer();

 private:
  void paintEvent(QPaintEvent*) override;
  void timerEvent(QTimerEvent* event) override;

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

  uint32_t timer_id_;
  std::shared_ptr<Connector> connector_;
};
