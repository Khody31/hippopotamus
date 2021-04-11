#include "system_manager.h"

void SystemManager::EntityDestroyed(Entity entity) {
  // no check because of the set
  for (auto const &[type_name, system_pointer] : systems_) {
    auto const& system = system_pointer;
    system->entities_.erase(entity);
  }
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature
entity_signature) {
  for (auto const &[type_name, system_pointer] : systems_) {
    auto const& type = type_name;
    auto const& system = system_pointer;
    auto const& system_signature = signatures_[type];

    if ((entity_signature & system_signature) == system_signature) {
      // match - insert into set
      system->entities_.insert(entity);
    } else {
      // no match - erase from set
      system->entities_.erase(entity);
    }
  }
}
