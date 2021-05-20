#include "garbage_system.h"

GarbageSystem::GarbageSystem(Coordinator* coordinator)
    : coordinator_(coordinator) {}

void GarbageSystem::Update() {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;
    coordinator_->DestroyEntity(entity);
  }
}
