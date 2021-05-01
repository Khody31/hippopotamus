#include "mouse_interface.h"
#include "systems/bullet_spawner.h"

void MouseInterface::OnPress(Qt::MouseButton button,
                             const QVector2D& game_coord) {
  if (button == Qt::LeftButton) {
    bullet_system_->CreateBulletFor(player_, game_coord);
  }
}

void MouseInterface::SetBulletSpawner(std::shared_ptr<BulletSpawner> bullet_system) {
  bullet_system_ = bullet_system;
}

void MouseInterface::SetPlayer(Entity player) {
  player_ = player;
}
