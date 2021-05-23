#pragma once

#include <QVector2D>

#include "engine/system.h"
#include "core/random_generator.h"

class Spawner;

class ArtifactSystem : public System {
 public:
  ArtifactSystem(Spawner* spawner, Coordinator* coordinator);
  void Update();

 private:
  void TrySpawnArtifact();
  void DeleteOldArtifacts();
  QVector2D GenerateSpawnPosition();

  int time_since_last_spawn_try_ = 0;

  Spawner* spawner_;
  Coordinator* coordinator_;
  RandomGenerator random_;
};
