#pragma once

#include <QVector2D>

#include "engine/types.h"
#include "engine/system.h"

class Coordinator;

class Spawner {
 public:
  explicit Spawner(Coordinator* coordinator);
  void CreateBulletFor(Entity entity, const QVector2D& destination_coord);

 private:
  Coordinator* coordinator_;
};
