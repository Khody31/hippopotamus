#include "component_manager.h"

ComponentManager::ComponentManager() : next_component_type_(0) {}

void ComponentManager::DestroyEntity(Entity entity) {
  for (auto const&[type_name, component_array]: component_arrays_) {
    auto const& component = component_array;

    component->DestroyEntity(entity);
  }
}
