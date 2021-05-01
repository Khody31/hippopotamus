#pragma once

#include <Qt>
#include <QVector2D>
#include <engine/types.h>

#include "engine/system.h"

class Coordinator;

class BulletSpawner {
 public:
  void CreateBulletFor(Entity entity, const QVector2D& destination_coord);
  void SetCoordinator(Coordinator* coordinator);

 private:
  Coordinator* coordinator_;
};
