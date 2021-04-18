#include "core/game_constants.h"
#include "components/components.h"
#include "movement_system.h"
#include "engine/coordinator.h"

void MovementSystem::Update(Coordinator* coordinator) {
  for (const auto& entity : entities_) {
    auto& motion_comp = coordinator->GetComponent<MotionComponent>(entity);
    auto& tr_comp = coordinator->GetComponent<TransformationComponent>(entity);
    tr_comp.pos += motion_comp.direction.normalized() * motion_comp.speed
        * game_constants::kTickTime / 1000;
  }
}
