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
      // todo (give player death animation and lock movement)
      connector_->BeginEndGameStage(false);
    } else {
      EntityType type =
          coordinator_->GetComponent<SerializationComponent>(entity).type;
      if (type == EntityType::kNecromancer ||
          type == EntityType::kShootingBoss) {
        bosses_alive_--;
      }
      coordinator_->DestroyEntity(entity);
      if (bosses_alive_ == 0) {
        connector_->PlaySound(GameSound::kPlayerWon);
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
