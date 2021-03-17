#pragma once

#include "Engine/Components/updatable_on_tick.h"
#include "Engine/Components/pixmap_component.h"
#include "Engine/Components/coordinates_base.h"
#include "Engine/Core/game_cotrolls_checker.h"


class Player : public UpdatableOnTick, public CoordinatesBase {
 public:
  Player() :
    pixmap_component_(new PixmapComponent(
        this,
        {0.5, 0.5},
        SceneLayerID::kBackground,
        ":/textures/some_basic_player.png"
        )){
  }

  void OnTick() override {
    if (GameControlsChecker::GetInstance().IsKeyPressed(Control::kMoveUp)) {
      coordinates_.y -= 0.01;
    }
    if (GameControlsChecker::GetInstance().IsKeyPressed(Control::kMoveDown)) {
      coordinates_.y += 0.01;
    }
    if (GameControlsChecker::GetInstance().IsKeyPressed(Control::kMoveRight)) {
      coordinates_.x += 0.01;
    }
    if (GameControlsChecker::GetInstance().IsKeyPressed(Control::kMoveLeft)) {
      coordinates_.x -= 0.01;
    }
  }

 private:
  PixmapComponent* pixmap_component_;
  Vector2D velocity_;
};
