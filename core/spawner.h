#pragma once

#include <QVector2D>

#include "engine/types.h"
#include "engine/system.h"
#include "entity_description.h"

class Coordinator;

class Spawner {
 public:
  explicit Spawner(Coordinator* coordinator);

  void CreateEntity(EntityType type, const QVector2D& pos);
  Entity CreateBulletFor(Entity entity, const QVector2D& destination_coord);
  Entity CreatePlayer(const QVector2D& pos);
  Entity CreateBall(const QVector2D& pos);
  std::array<Entity, 4> CreateWalls();
  std::array<Entity, 4> CreateDoors();

 private:
  Entity CreateDoor(const QVector2D& pos, const QVector2D& size);
  Entity CreateWall(const QVector2D& pos, const QVector2D& size);
  Coordinator* coordinator_;
};
