#include "game_components/components.h"
#include "transformation_system.h"

void TransformationSystem::Update(Coordinator* game_coordinator) {
  for (auto const& entity : entities_) {
    auto& tr_comp = game_coordinator->GetComponent<TransformationComponent>
        (entity);
  }
}
