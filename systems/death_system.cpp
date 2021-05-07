#include "death_system.h"

#include "components/components.h"
#include "engine/coordinator.h"

void DeathSystem::Update(Coordinator* coordinator) {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;
    HealthComponent health_component =
        coordinator->GetComponent<HealthComponent>(entity);
    if (health_component.health < 0) {
      coordinator->DestroyEntity(entity);
    }
  }
}
