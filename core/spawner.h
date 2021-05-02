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
  void CreateBulletFor(Entity entity, const QVector2D& destination_coord);
  Entity CreatePlayer(const QVector2D& pos);
  void CreateBall(const QVector2D& pos);
  void CreateWall(const QVector2D& pos);

 private:
  Coordinator* coordinator_;
};
