#include "engine/comp/logic_component.h"
#include "logic_governor.h"

LogicGovernor::LogicGovernor() : Governor(ComponentIDs::kLogicID) {}

void LogicGovernor::OnTick() {
  for (Component* child : GetComponents()) {
    dynamic_cast<LogicComponent*>(child)->OnTick();
  }
}
