#pragma once

#include <QWidget>

class GameScene : public QWidget {
 public:
  GameScene();
 private:
  void paintEvent(QPaintEvent*) override;
  void timerEvent(QTimerEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
};