#pragma once

#include "engine/coordinator.h"
#include "descriptions.h"

class Spawner {
 public:
  explicit Spawner(Coordinator* coordinator);

  void CreateEntity(EntityType type, const QVector2D& pos);
  void CreateBullet(Entity entity, const QVector2D& destination_coord);

  Entity CreatePlayer(const QVector2D& pos);
  Entity CreateLittleSkeleton(const QVector2D& pos);
  Entity CreateCleverBot(const QVector2D& pos);
  Entity CreateAngryPlant(const QVector2D& pos);
  Entity CreateSmellingPlant(const QVector2D& pos);
  Entity CreateBigSkeleton(const QVector2D& pos);

  void CreateBall(const QVector2D& pos);
  void CreateWalls();
  void CreateDoors(const std::array<int32_t, 4>& rooms);

 private:
  Entity CreateDoor(const QVector2D& coordinates,
                    const QVector2D& size,
                    const QVector2D& player_position,
                    int32_t associated_room);
  void CreateWall(const QVector2D& pos, const QVector2D& size);

  Coordinator* coordinator_;
};
