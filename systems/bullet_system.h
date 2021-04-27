#pragma once

#include <Qt>
#include <QVector2D>
#include <engine/types.h>

#include "engine/system.h"

class Coordinator;

class BulletSystem : public System {
 public:
  void CreateBulletFor(Entity entity, const QVector2D& game_coord);
  void SetCoordinator(Coordinator* coordinator);

 private:
  Coordinator* coordinator_;
};
