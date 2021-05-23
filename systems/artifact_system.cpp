#include "components/components.h"
#include <engine/coordinator.h>
#include "artifact_system.h"
#include "core/constants.h"
#include "core/spawner.h"

void ArtifactSystem::Update() {
  DeleteOldArtifacts();
  TrySpawnArtifact();
}

QVector2D ArtifactSystem::GenerateSpawnPosition() {
  QVector2D range = constants::kMaxArtifactCoordinates
      - constants::kMinArtifactCoordinates;
  int range_x = 1000 * range.x();
  int range_y = 1000 * range.y();
  float x = constants::kMinArtifactCoordinates.x()
      + static_cast<float>(Rand() % range_x) / 1000;
  float y = constants::kMinArtifactCoordinates.y()
      + static_cast<float>(Rand() % range_y) / 1000;
  return {x, y};
}

ArtifactSystem::ArtifactSystem(Spawner* spawner, Coordinator* coordinator)
    : spawner_(spawner), coordinator_(coordinator) {}

void ArtifactSystem::TrySpawnArtifact() {
  if (time_since_last_spawn_try_ms < constants::kTrySpawnArtifactPeriod_ms) {
    time_since_last_spawn_try_ms += constants::kTickTime;
    return;
  }

  if (Rand() % constants::kInvArtifactSpawnChance == 0) {
    auto buff_type =
        static_cast<BuffType>(Rand() % static_cast<int>(BuffType::kEnumSize));
    spawner_->CreateArtifact(GenerateSpawnPosition(), buff_type);
  }
  time_since_last_spawn_try_ms = 0;
}

void ArtifactSystem::DeleteOldArtifacts() {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *(it++);
    auto& artifact_comp = coordinator_->GetComponent<ArtifactComponent>(entity);
    if (artifact_comp.existing_time < constants::kMaxArtifactExistingTime_ms) {
      artifact_comp.existing_time += constants::kTickTime;
    } else {
      coordinator_->DestroyEntity(entity);
    }
  }
}

/// Temporary solution.
uint32_t ArtifactSystem::Rand() {
  static unsigned int seed = 3;
  return rand_r(&seed);
}
