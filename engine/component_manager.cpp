#include "component_manager.h"

ComponentManager::ComponentManager() : next_component_type_(0) {}

void ComponentManager::DestroyEntity(Entity entity) {
  for (auto const& pair : component_arrays_) {
    auto const& component = pair.second;

    component->DestroyEntity(entity);
  }
}
