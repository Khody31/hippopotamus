#pragma once

#include "engine/coordinator.h"
#include "descriptions.h"

#include "components/components.h"
#include "random_generator.h"

class Connector;

class Spawner : public QObject {
 public:
  explicit Spawner(Coordinator* coordinator,
                   Connector* connector,
                   Entity* player);

  void CreateEntity(EntityType type, const QVector2D& pos);
  void CreateBullet(Entity entity, const QVector2D& destination_coord);

  Entity CreatePlayer(const QVector2D& pos);
  void CreateLittleSkeleton();
  Entity CreateCleverBot(const QVector2D& pos);
  Entity CreateAngryPlant(const QVector2D& pos);
  Entity CreateSmellingPlant(const QVector2D& pos);
  Entity CreateNecromancer(const QVector2D& pos);
  Entity CreateShootingBoss(const QVector2D& pos);

  void CreateBall(const QVector2D& pos);
  void CreateWalls();
  void CreateDoors(const std::array<int32_t, 4>& rooms);

  Entity CreateArtifact(const QVector2D& position, BuffType::Buff buff_type);

 private:
  Entity CreateDoor(const QVector2D& coordinates,
                    const QVector2D& size,
                    const QVector2D& player_position,
                    int32_t associated_room);
  void CreateWall(const QVector2D& pos, const QVector2D& size);

  Coordinator* coordinator_;
  Connector* connector_;
  Entity* player_;
  RandomGenerator random_generator_;
};
