#include "player.h"

Player::Player() : GameObject(EntityID::kPlayer) {
  transformation_component_ = new TransformationComponentPlayer;
  pixmap_component_ = new PixmapComponent(
      this, {0.5, 0.5}, SceneLayerID::kBackground,
      ":/textures/some_basic_player.png");
}

void Player::OnTick() {
  transformation_component_->Update();
  pixmap_component_->Update();
}
