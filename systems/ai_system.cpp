#include "ai_system.h"

void AiSystem::Update(QVector2D player_pos, Coordinator* coordinator) {
  for (const auto& entity : entities_) {
    auto& motion_comp = coordinator->GetComponent<MotionComponent>(entity);
    auto& transform_comp = coordinator->GetComponent<TransformationComponent>(entity);
    motion_comp.direction = (player_pos - transform_comp.pos).normalized();
    motion_comp.speed = 1;
  }
}
