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

  int time_since_last_spawn_try_ms = 0;

  Spawner* spawner_;
  Coordinator* coordinator_;
};
