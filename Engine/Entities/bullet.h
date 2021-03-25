#pragma once

#include "Engine/Core/game_object.h"
#include "Engine/Components/pixmap_component.h"

class Bullet : GameObject {
 public:
  explicit Bullet(const Vector2D& pos, const Vector2D& velocity);
  void OnTick() override;
};
