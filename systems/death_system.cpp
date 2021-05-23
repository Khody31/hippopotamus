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
      // todo (give player death animation and lock movement)
      connector_->BeginEndGameStage(false);
    } else {
      coordinator_->DestroyEntity(entity);
      enemies_alive--;
      if (enemies_alive == 0) {
        connector_->BeginEndGameStage(true);
      }
    }
  }
}

DeathSystem::DeathSystem(Coordinator* coordinator,
                         Connector* connector,
                         Entity* player) :
    coordinator_(coordinator),
    player_(player),
    connector_(connector) {}
