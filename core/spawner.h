#pragma once

#include "components/components.h"
#include "engine/coordinator.h"
#include "descriptions.h"
#include "random_generator.h"
#include "utilities/cache.h"

class Connector;

class Spawner : public QObject {
 public:
  explicit Spawner(Coordinator* coordinator,
                   Connector* connector,
                   Entity* player,
                   Cache* cache);

  void CreateEntity(EntityType type, const QVector2D& pos);
  void CreateBullet(Entity entity, const QVector2D& destination_coord);

  Entity CreatePlayer(const QVector2D& pos);
  Entity CreateLittleSkeleton(const QVector2D& pos);
  Entity CreateWasp(const QVector2D& position);
  Entity CreateBouncingTotem(const QVector2D& position);
  Entity CreateBattleTotem(const QVector2D& pos);
  Entity CreateNecromancer(const QVector2D& pos);
  Entity CreateShootingBoss(const QVector2D& pos);

  void CreateWalls();
  void CreateDoors(const std::array<int32_t, 4>& rooms);
  void CreateBackground();
  void CreateDecor(EntityType type, const QVector2D& position);
  void CreatePile(EntityType type, const QVector2D& position);
  void CreateTutorial();

  Entity CreateArtifact(const QVector2D& position, BuffType::Buff buff_type);

 private:
  Entity CreateDoor(const QVector2D& coordinates,
                    const QVector2D& collider_size,
                    const QVector2D& pixmap_size,
                    const QVector2D& player_position,
                    int32_t associated_room,
                    QPixmap* pixmap,
                    SceneLayers layer);
  void CreateWall(const QVector2D& pos, const QVector2D& size);

  Coordinator* coordinator_;
  Connector* connector_;
  Entity* player_;
  RandomGenerator random_generator_;
  Cache* cache_;
};
