#include "bullet.h"
#include "Engine/Components/transformation_component_bullet.h"

Bullet::Bullet(const Vector2D& pos, const Vector2D& velocity)
    : GameObject(Entity::kBullet) {
  transformation_component_ = new TransformationComponentBullet;
  transformation_component_->SetCoordinates(pos);
  transformation_component_->SetVelocity(velocity);

  pixmap_component_ = new PixmapComponent(
      this, {0.2, 0.2}, SceneLayerID::kBackground,
      ":/textures/fireball.png");
}

void Bullet::OnTick() {
  transformation_component_->Update();
}
