#include "coordinator.h"

Coordinator::Coordinator() :
    component_manager_(std::make_unique<ComponentManager>()),
    entity_manager_(std::make_unique<EntityManager>()),
    system_manager_(std::make_unique<SystemManager>()) {
}

Entity Coordinator::CreateEntity() {
  return entity_manager_->CreateEntity();
}

void Coordinator::DestroyEntity(Entity entity) {
  entity_manager_->DestroyEntity(entity);
  component_manager_->DestroyEntity(entity);
  system_manager_->EntityDestroyed(entity);
}
