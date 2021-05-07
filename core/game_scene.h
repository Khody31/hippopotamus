#pragma once

#include <QWidget>
#include <QTimerEvent>
#include <memory>

#include "game_constants.h"
#include "core/connector.h"
#include "view/abstract_controller.h"

class GameScene : public QWidget {
  Q_OBJECT
 public:
  explicit GameScene(std::shared_ptr<Connector> connector,
                     std::shared_ptr<AbstractController> controller, QWidget* parent);

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
  std::shared_ptr<Connector> connector_;
  std::shared_ptr<AbstractController> controller_;
};
