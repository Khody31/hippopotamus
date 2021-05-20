#include "death_system.h"

#include "components/components.h"

void DeathSystem::Update() {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;

    HealthComponent health =
        coordinator_->GetComponent<HealthComponent>(entity);
    if (health.value > 0) {
      continue;
    }

    if (entity == *player_) {
      scene_->OnLoss();
      return;
    } else {
      coordinator_->DestroyEntity(entity);
      enemies_alive--;
      if (enemies_alive == 0) {
        scene_->OnWin();
        return;
      }
    }
  }
}


DeathSystem::DeathSystem(Coordinator* coordinator,
                         Scene* scene, Entity* player) :
    coordinator_(coordinator), scene_(scene), player_(player) {
}
