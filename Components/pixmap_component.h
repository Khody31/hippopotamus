#pragma once

#include <QGraphicsItem>

#include "Core/game_scene.h"

class PixmapComponent : public QGraphicsPixmapItem {
 public:
  PixmapComponent() {
    GameScene::GetInstance().addItem(this);
  }
  ~PixmapComponent() override {
    GameScene::GetInstance().removeItem(this);
  }
};
