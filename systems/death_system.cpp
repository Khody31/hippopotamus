#include "death_system.h"

#include "components/components.h"

void DeathSystem::Update() {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;

    coordinator_->GetComponent<HealthComponent>(entity);
    if (coordinator_->GetComponent<HealthComponent>(entity).value > 0) {
      continue;
    }
    if (entity == *player_) {
      scene_->OnLoss();
      return;
    }

    EntityType type =
        coordinator_->GetComponent<SerializationComponent>(entity).type;
    if (type == EntityType::kBigSkeleton ||
        type == EntityType::kShootingBoss) {
      bosses_alive_--;
    }

    coordinator_->DestroyEntity(entity);
    if (bosses_alive_ == 0) {
      scene_->OnWin();
      return;
    }
  }
}

DeathSystem::DeathSystem(Coordinator* coordinator,
                         Scene* scene, Entity* player) :
    coordinator_(coordinator), scene_(scene), player_(player) {
}
