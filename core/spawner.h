#pragma once

#include "engine/types.h"
#include "engine/system.h"
#include "descriptions.h"

class Spawner {
 public:
  explicit Spawner(Coordinator* coordinator);

  void CreateEntity(EntityType type, const QVector2D& position);
  void CreateBullet(Entity entity, const QVector2D& cursor_position);
  Entity CreatePlayer(const QVector2D& position);
  void CreateBall(const QVector2D& position);
  void CreateWalls();
  std::array<Entity, 4> CreateDoors();

 private:
  Entity CreateDoor(const QVector2D& position,
                    const QVector2D& size,
                    const QVector2D& player_position);
  void CreateWall(const QVector2D& position, const QVector2D& size);

  Coordinator* coordinator_;
};
