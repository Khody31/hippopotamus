#include <engine/coordinator.h>
#include "artifact_system.h"
#include "core/constants.h"
#include "components/components.h"
#include "core/spawner.h"

void ArtifactSystem::Update() {
  if (time_since_last_check_ms < check_period_ms_) {
    time_since_last_check_ms += constants::kTickTime;
    return;
  }

  if (rand() % inv_spawn_chance_ == 0) {
    auto buff_type =
        static_cast<BuffType>(rand() % static_cast<int>(BuffType::kEnumSize));
    spawner_->CreateArtifact(GenerateSpawnPosition(), buff_type);
  }
  time_since_last_check_ms = 0;
}

QVector2D ArtifactSystem::GenerateSpawnPosition() {
  QVector2D range = constants::kMaxArtifactCoordinates
      - constants::kMinArtifactCoordinates;
  int range_x = 1000.f * range.x();
  int range_y = 1000.f * range.y();
  float x = constants::kMinArtifactCoordinates.x()
      + static_cast<float>(rand() % range_x) / 1000.f;
  float y = constants::kMinArtifactCoordinates.y()
      + static_cast<float>(rand() % range_y) / 1000.f;
  return {x, y};
}

ArtifactSystem::ArtifactSystem(Entity* player, Spawner* spawner)
    : player_(player), spawner_(spawner) {}
