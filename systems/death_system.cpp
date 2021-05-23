#include "death_system.h"
#include "components/components.h"
#include "core/connector.h"
#include "core/constants.h"

#include <QTimer>

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
      connector_->PlaySound(GameSound::kPlayerDead);
      scene_->OnLoss();
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
        QTimer::singleShot(constants::kTimeBetweenEndGameAndMenuSwitch,
                           scene_,
                           &Scene::OnWin);
      }
    }
  }
}

DeathSystem::DeathSystem(Coordinator* coordinator,
                         Connector* connector,
                         Entity* player,
                         Scene* scene) :
    coordinator_(coordinator),
    player_(player),
    scene_(scene),
    connector_(connector) {}
