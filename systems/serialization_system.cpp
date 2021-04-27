#include "serialization_system.h"

void SerializationSystem::Serialize() {
  Room current_room;
  // logic of conversion state into Room exemplar
  for (const auto& entity : entities_) {
    // auto& tr_comp = game_coordinator->GetComponent<TransformationComponent>
    //     (entity);
  }
  LoadToJson(current_room);
}

void SerializationSystem::Deserialize(Coordinator* coordinator, int id) {
  Room next_room = LoadFromJson(id);
  // logic of conversion Room exemplar into state
}

void SerializationSystem::DestroyAllEntities() {
  // delete all entities from the set of entities of this system

}


