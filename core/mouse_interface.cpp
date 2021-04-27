#include "mouse_interface.h"
#include "systems/bullet_system.h"

void MouseInterface::OnPress(Qt::MouseButton button,
                             const QVector2D& game_coord) {
  if (button == Qt::LeftButton) {
    bullet_system_->CreateBulletFor(player_, game_coord);
  }
}

void MouseInterface::SetBulletSystem(std::shared_ptr<BulletSystem> bullet_s) {
  bullet_system_ = bullet_s;
}

void MouseInterface::SetPlayer(Entity player) {
  player_ = player;
}
