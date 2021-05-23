#pragma once

#include <QVector2D>

#include "engine/system.h"

class Spawner;

class ArtifactSystem : public System {
 public:
  ArtifactSystem(Spawner* spawner, Coordinator* coordinator);

  void Update();

  void TrySpawnArtifact();
  void DeleteOldArtifacts();

 private:
  QVector2D GenerateSpawnPosition();
  uint32_t Rand();

  const int try_spawn_period_ms_ = 20;
  const int inv_spawn_chance_ = 100;
  const int max_existing_time_ms_ = 3'000;
  int time_since_last_spawn_try_ms = 0;

  Spawner* spawner_;
  Coordinator* coordinator_;
};
