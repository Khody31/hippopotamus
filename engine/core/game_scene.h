#pragma  once

#include <QWidget>

#include "engine/gov/governor.h"

class GameScene : public Governor, public QWidget {
 public:
  GameScene();
  void OnTick() override;

  void paintEvent(QPaintEvent*) override;

 private:

};
