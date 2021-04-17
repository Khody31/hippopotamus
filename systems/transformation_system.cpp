#include "components/components.h"
#include "transformation_system.h"

void TransformationSystem::Update(Coordinator* coordinator) {
  for (auto const& entity : entities_) {
    auto& tr_comp = coordinator->GetComponent<TransformationComponent>
        (entity);
  }
}
