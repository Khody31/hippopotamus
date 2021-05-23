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

    EntityType type =
        coordinator_->GetComponent<SerializationComponent>(entity).type;
    if (type == EntityType::kNecromancer ||
        type == EntityType::kShootingBoss) {
      bosses_alive_--;
    }

    coordinator_->DestroyEntity(entity);

    if (bosses_alive_ == 0) {
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
