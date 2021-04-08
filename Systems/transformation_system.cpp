#include "Components/components.h"
#include "transformation_system.h"

void TransformationSystem::Update(const QVector2D &pos) {
for(auto const& entity : mEntities) {
  auto& tr_comp = game_coordinator.GetComponent<TransformationComponent>
      (entity);
  tr_comp.pos_ = pos;
}
}
