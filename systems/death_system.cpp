#include "death_system.h"

#include "components/components.h"
#include "core/connector.h"

void DeathSystem::Update() {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;

    coordinator_->GetComponent<HealthComponent>(entity);
    if (coordinator_->GetComponent<HealthComponent>(entity).value > 0) {
      continue;
    }
    if (entity == *player_) {
      connector_->PlaySound(GameSound::kPlayerDead);
      scene_->OnLoss();
      return;
    }

    coordinator_->DestroyEntity(entity);
    enemies_alive--;
    if (enemies_alive == 0) {
      connector_->PlaySound(GameSound::kPlayerWon);
      scene_->OnWin();
      return;
    }
  }
}

DeathSystem::DeathSystem(Coordinator* coordinator,
                         Connector* connector,
                         Scene* scene, Entity* player) :
    coordinator_(coordinator),
    connector_(connector),
    scene_(scene),
    player_(player) {}
