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
  return constants::kMinArtifactCoordinates + QVector2D{
                                              random_.GetReal(0.f, range.x()),
                                              random_.GetReal(0.f, range.y())};
}

ArtifactSystem::ArtifactSystem(Spawner* spawner, Coordinator* coordinator)
    : spawner_(spawner), coordinator_(coordinator) {}

void ArtifactSystem::TrySpawnArtifact() {
  if (time_since_last_spawn_try_ < constants::kTrySpawnArtifactPeriod) {
    time_since_last_spawn_try_ += constants::kTickTime;
    return;
  }

  if (random_.GetInt(1, constants::kInvArtifactSpawnChance) == 1) {
    auto buff_type =
        static_cast<BuffType::Buff>(random_.GetInt(0, BuffType::kEnumSize - 1));
    spawner_->CreateArtifact(GenerateSpawnPosition(), buff_type);
  }
  time_since_last_spawn_try_ = 0;
}

void ArtifactSystem::DeleteOldArtifacts() {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *(it++);
    auto& artifact_comp = coordinator_->GetComponent<ArtifactComponent>(entity);
    if (artifact_comp.lifetime < constants::kMaxArtifactExistingTime) {
      artifact_comp.lifetime += constants::kTickTime;
    } else {
      coordinator_->DestroyEntity(entity);
    }
  }
}
