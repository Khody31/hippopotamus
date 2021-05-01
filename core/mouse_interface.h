#pragma once

#include <Qt>
#include <QVector2D>

#include <memory>
#include <engine/types.h>

class Spawner;

class MouseInterface {
 public:
  void OnPress(Qt::MouseButton button, const QVector2D& game_coord);
  void SetBulletSpawner(std::shared_ptr<Spawner> bullet_system);
  void SetPlayer(Entity player);

 private:
  std::shared_ptr<Spawner> bullet_spawner_;
  Entity player_;
};
