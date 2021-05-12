#include "movement_system.h"

#include "core/constants.h"
#include "components/components.h"
#include "engine/coordinator.h"

MovementSystem::MovementSystem(Coordinator* coordinator) :
    coordinator_(coordinator) {}

void MovementSystem::Update() {
  for (const auto& entity : entities_) {
    auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
    auto& transform =
        coordinator_->GetComponent<TransformationComponent>(entity);
    transform.pos += motion.direction.normalized() * motion.speed
        * game_constants::kTickTime / 1000;
  }
}



