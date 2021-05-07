#include "ai_system.h"
#include <iostream>

void ApplyStupidTactic(QVector2D player_pos, Coordinator* coordinator, Entity
                                                                      entity) {
  auto& ai_comp = coordinator->GetComponent<AiComponent>(entity);
  auto& motion_comp = coordinator->GetComponent<MotionComponent>(entity);
  auto& transform_comp =
      coordinator->GetComponent<TransformationComponent>(entity);
  motion_comp.direction = (player_pos - transform_comp.pos).normalized();
  motion_comp.speed = 0.7;
}

void ApplyStandingTactic(Coordinator* coordinator, Entity entity) {
  auto& motion_comp = coordinator->GetComponent<MotionComponent>(entity);
  motion_comp.speed = 0;
}

void AiSystem::Update(QVector2D player_pos, Coordinator* coordinator) {
  for (const auto& entity : entities_) {
    switch (coordinator->GetComponent<AiComponent>(entity).type) {
      case AiType::kStupid : {
        ApplyStupidTactic(player_pos, coordinator, entity);
        break;
      }
      case AiType::kStanding : {
        ApplyStandingTactic(coordinator, entity);
        break;
      }
      default: {
        throw "Unknown enemy";
      }
    }
  }
}
