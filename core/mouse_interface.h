#pragma once

#include <Qt>
#include <QVector2D>

#include <memory>
#include <engine/types.h>

class BulletSpawner;

class MouseInterface {
 public:
  void OnPress(Qt::MouseButton button, const QVector2D& game_coord);
  void SetBulletSpawner(std::shared_ptr<BulletSpawner> bullet_system);
  void SetPlayer(Entity player);

 private:
  std::shared_ptr<BulletSpawner> bullet_system_;
  Entity player_;
};
