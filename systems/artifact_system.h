#pragma once

#include <QVector2D>
#include "engine/system.h"

class Spawner;

class ArtifactSystem : public System {
 public:
  ArtifactSystem(Entity* player, Spawner* spawner);

  void Update();

 private:
  QVector2D GenerateSpawnPosition();

  const int check_period_ms_ = 20;
  const int inv_spawn_chance_ = 2;

  int time_since_last_check_ms = 0;

  Entity* player_; //todo
  Spawner* spawner_; //todo
};
