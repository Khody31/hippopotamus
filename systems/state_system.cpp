#include <algorithm>

#include "engine/coordinator.h"
#include "state_system.h"
#include "components/components.h"
#include "core/constants.h"

StateSystem::StateSystem(Coordinator* coordinator)
    : coordinator_(coordinator) {}

void StateSystem::Update() {
  for (Entity entity : entities_) {
    auto& state_comp = coordinator_->GetComponent<StateComponent>(entity);
    for (auto& buff_time_left : state_comp.buff_to_time) {
      buff_time_left = std::max(
          0, buff_time_left - static_cast<int32_t>(constants::kTickTime));
    }
  }
}
