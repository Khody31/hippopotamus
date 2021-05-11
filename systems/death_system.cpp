#include "death_system.h"

#include "components/components.h"
#include "engine/coordinator.h"
#include "core/scene.h"

void DeathSystem::Update() {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;

    HealthComponent health =
        coordinator_->GetComponent<HealthComponent>(entity);
    if (health.value > 0) {
      continue;
    }

    if (entity == player_) {
      scene_->OnLoss();
    } else {
      coordinator_->DestroyEntity(entity);
    }
  }
}

void DeathSystem::SetPlayer(Entity player) {
  player_ = player;
}

DeathSystem::DeathSystem(Coordinator* coordinator, Scene* scene) :
    coordinator_(coordinator), scene_(scene) {
}
