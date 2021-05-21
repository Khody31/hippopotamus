#include "movement_system.h"

#include "core/constants.h"
#include "components/components.h"

MovementSystem::MovementSystem(Coordinator* coordinator) :
    coordinator_(coordinator) {}

void MovementSystem::Update() {
  for (const auto& entity : entities_) {
    auto& motion = coordinator_->GetComponent<MotionComponent>(entity);
    auto& transform =
        coordinator_->GetComponent<TransformationComponent>(entity);
    transform.position += motion.direction.normalized() * motion.current_speed
        * constants::kTickTime / 1000;
  }
}



