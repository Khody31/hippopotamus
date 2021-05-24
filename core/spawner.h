#pragma once

#include "components/components.h"
#include "engine/coordinator.h"
#include "descriptions.h"

#include "components/components.h"

class Connector;

class Spawner {
 public:
  explicit Spawner(Coordinator*, Connector*, Entity*);

  void CreateEntity(EntityType type, const QVector2D& pos);
  void CreateBullet(Entity entity, const QVector2D& destination_coord);

  Entity CreatePlayer(const QVector2D& pos);
  Entity CreateLittleSkeleton(const QVector2D& pos);
  Entity CreateCleverBot(const QVector2D& pos);
  Entity CreateAngryPlant(const QVector2D& pos);
  Entity CreateSmellingPlant(const QVector2D& pos);
  Entity CreateNecromancer(const QVector2D& pos);
  Entity CreateShootingBoss(const QVector2D& pos);

  void CreateBall(const QVector2D& pos);
  void CreateWalls();
  void CreateDoors(const std::array<int32_t, 4>& rooms);
  void CreateBackground();
  void CreateDecor(EntityType type, const QVector2D& position);
  void CreatePile(EntityType type, const QVector2D& position);

  Entity CreateArtifact(const QVector2D& position, BuffType::Buff buff_type);

 private:
  Entity CreateDoor(const QVector2D& coordinates,
                    const QVector2D& size,
                    const QVector2D& player_position,
                    int32_t associated_room,
                    QPixmap* pixmap,
                    SceneLayers layer);
  void CreateWall(const QVector2D& pos, const QVector2D& size);

  Coordinator* coordinator_;
  Connector* connector_;
  Entity* player_;
};
