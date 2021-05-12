#pragma once

#include "engine/types.h"
#include "engine/system.h"
#include "entity_description.h"

class Spawner {
 public:
  explicit Spawner(Coordinator* coordinator);

  void CreateEntity(EntityType type, const QVector2D& pos);
  void CreateBullet(Entity entity, const QVector2D& destination_coord);
  Entity CreatePlayer(const QVector2D& pos);
  Entity CreateStupidBot(const QVector2D& pos);
  Entity CreateCleverBot(const QVector2D& pos);
  Entity CreateAngryPlant(const QVector2D& pos);
  void CreateBall(const QVector2D& pos);
  void CreateWalls();
  std::array<Entity, 4> CreateDoors();

 private:
  Entity CreateDoor(const QVector2D& pos, const QVector2D& size);
  void CreateWall(const QVector2D& pos, const QVector2D& size);

  Coordinator* coordinator_;
};
