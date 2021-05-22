#include "components/components.h"
#include <engine/coordinator.h>
#include "artifact_system.h"
#include "core/constants.h"
#include "core/spawner.h"

void ArtifactSystem::Update() {
  ControlPlayerBuff();
  DeleteOldArtifacts();
  TrySpawnArtifact();
}

QVector2D ArtifactSystem::GenerateSpawnPosition() {
  QVector2D range = constants::kMaxArtifactCoordinates
      - constants::kMinArtifactCoordinates;
  int range_x = 1000.f * range.x();
  int range_y = 1000.f * range.y();
  float x = constants::kMinArtifactCoordinates.x()
      + static_cast<float>(Rand() % range_x) / 1000.f;
  float y = constants::kMinArtifactCoordinates.y()
      + static_cast<float>(Rand() % range_y) / 1000.f;
  return {x, y};
}

ArtifactSystem::ArtifactSystem(Spawner* spawner, Coordinator* coordinator)
    : spawner_(spawner), coordinator_(coordinator) {}

void ArtifactSystem::TrySpawnArtifact() {
  if (time_since_last_spawn_try_ms < try_spawn_period_ms_) {
    time_since_last_spawn_try_ms += constants::kTickTime;
    return;
  }

  if (Rand() % inv_spawn_chance_ == 0) {
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
    if (artifact_comp.existing_time < max_existing_time_ms_) {
      artifact_comp.existing_time += constants::kTickTime;
    } else {
      coordinator_->DestroyEntity(entity);
    }
  }
}

void ArtifactSystem::GivePlayerBuff(BuffType buff_type) {
  current_player_buff_ = buff_type;
}

void ArtifactSystem::ControlPlayerBuff() {
  if (current_player_buff_ == BuffType::kNone) {
    return;
  }
  if (time_player_has_buff_ms_ > max_buff_time_for_player_ms_) {
    time_player_has_buff_ms_ = 0;
    current_player_buff_ = BuffType::kNone;
  } else {
    time_player_has_buff_ms_ += constants::kTickTime;
  }
}

BuffType ArtifactSystem::GetPlayerBuff() const {
  return current_player_buff_;
}

/// Temporary solution.
uint32_t ArtifactSystem::Rand() {
  static unsigned int seed = 3;
  return rand_r(&seed);
}
