#include "component_manager.h"

ComponentManager::ComponentManager() : next_component_type_(0) {}

void ComponentManager::DestroyEntity(Entity entity) {
  for (auto const&[type_name, component] : component_arrays_) {
    component->DestroyEntity(entity);
  }
}
