#pragma once

#include "engine/coordinator.h"
#include "descriptions.h"

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
  std::array<Entity, 4> CreateDoors(
      const std::array<int32_t, 4>& associated_rooms);

 private:
  Entity CreateDoor(QVector2D coordinates, QVector2D size,
                    QVector2D player_pos, int32_t associated_room);
  void CreateWall(const QVector2D& pos, const QVector2D& size);

  Coordinator* coordinator_;
};
