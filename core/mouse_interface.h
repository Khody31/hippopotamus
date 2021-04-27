#pragma once

#include <Qt>
#include <QVector2D>

#include <memory>
#include <engine/types.h>

class BulletSystem;

class MouseInterface {
 public:
  void OnPress(Qt::MouseButton button, const QVector2D& game_coord);
  void SetBulletSystem(std::shared_ptr<BulletSystem> bullet_system);
  void SetPlayer(Entity player);

 private:
  std::shared_ptr<BulletSystem> bullet_system_;
  Entity player_;
};
