#pragma once

#include <QGraphicsScene>
#include "Miscellaneous/singleton.h"

class GameScene : public Singleton, public QGraphicsScene {
 public:
  static GameScene& GetInstance() {
    static GameScene instance;
    return instance;
  }
};
