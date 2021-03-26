#pragma once

#include <QVector2D>

#include "engine/core/game_object.h"
#include "engine/components/pixmap_component.h"

class Bullet : GameObject {
 public:
  explicit Bullet(const QVector2D& pos, const QVector2D& velocity);
  void OnTick() override;
};
