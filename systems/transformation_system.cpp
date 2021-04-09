#include "game_components/components.h"
#include "transformation_system.h"
#include "engine/constants.h"

void TransformationSystem::Update(const QVector2D &pos) {
for(auto const& entity : entities_) {
  auto& tr_comp = game_coordinator.GetComponent<TransformationComponent>
      (entity);
  tr_comp.pos_ = pos;
}
}
