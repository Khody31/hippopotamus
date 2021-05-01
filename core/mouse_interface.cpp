#include "mouse_interface.h"
#include "spawner.h"

void MouseInterface::OnPress(Qt::MouseButton button,
                             const QVector2D& game_coord) {
  if (button == Qt::LeftButton) {
    bullet_spawner_->CreateBulletFor(player_, game_coord);
  }
}

void MouseInterface::SetBulletSpawner(
    std::shared_ptr<Spawner> bullet_spawner) {
  bullet_spawner_ = bullet_spawner;
}

void MouseInterface::SetPlayer(Entity player) {
  player_ = player;
}
