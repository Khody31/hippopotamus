#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include <QWidget>

#include "engine/gov/governor.h"

class GameScene : public Governor, public QWidget {
 public:
  GameScene();
  void OnTick() override;

  void paintEvent(QPaintEvent*) override;

 private:

};

#endif  // GAME_SCENE_H_
