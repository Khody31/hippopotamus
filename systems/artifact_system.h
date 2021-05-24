#pragma once

#include <QVector2D>

#include "engine/system.h"
#include "core/random_generator.h"

class Spawner;
class Connector;

class ArtifactSystem : public System {
 public:
  ArtifactSystem(Spawner*, Coordinator*, Connector*);
  void Update();

 private:
  void TrySpawnArtifact();
  void DeleteOldArtifacts();
  QVector2D GenerateSpawnPosition();

  int time_since_last_spawn_try_ = 0;

  Spawner* spawner_;
  Coordinator* coordinator_;
  Connector* connector_;
  RandomGenerator random_;
};
