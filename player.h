#pragma once

#include "Engine/Components/updatable_on_tick.h"
#include "Engine/Components/pixmap_component.h"
#include "Engine/Components/transformation_component.h"
#include "Engine/Core/keyboard_interface.h"
#include "Engine/Core/game_object.h"


class Player : public UpdatableOnTick, public GameObject {
 public:
  Player() {
    pixmap_component_ = new PixmapComponent(
        this, {0.5, 0.5}, SceneLayerID::kBackground,
        ":/textures/some_basic_player.png");
    transformation_component_ = new TransformationComponent;
  }

  void OnTick() override {
    if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveUp)) {
      transformation_component_->MoveBy({0, -0.07});
    }
    if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveDown)) {
      transformation_component_->MoveBy({0, 0.07});
    }
    if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveRight)) {
      transformation_component_->MoveBy({0.07, 0});
    }
    if (KeyboardInterface::GetInstance().IsKeyPressed(Control::kMoveLeft)) {
      transformation_component_->MoveBy({-0.07, 0});
    }
  }

 private:
  Vector2D velocity_;
};
