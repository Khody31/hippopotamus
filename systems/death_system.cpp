#include "death_system.h"

#include "components/components.h"
#include "engine/coordinator.h"
#include "core/game_scene.h"

void DeathSystem::Update(Coordinator* coordinator) {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;
    HealthComponent health_component =
        coordinator->GetComponent<HealthComponent>(entity);
    if (health_component.health < 0) {
      if (entity == player_) {
        scene_->OnLoss();
      } else {
        coordinator->DestroyEntity(entity);
      }
    }
  }
}

void DeathSystem::SetScene(GameScene* scene) {
  scene_ = scene;
}

void DeathSystem::SetPlayer(Entity player) {
  player_ = player;
}
