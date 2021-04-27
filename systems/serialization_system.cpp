#include "serialization_system.h"

void SerializationSystem::Serialize(Coordinator* coordinator) {
  Room current_room;
  for (const auto& entity : entities_) {
    current_room.AddDescription(CreateDescription(entity, coordinator));
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

EntityDescription SerializationSystem::CreateDescription(Entity entity,
                                                         Coordinator* coordinator) {
  EntityDescription description;
  if (coordinator->HasComponent<TransformationComponent>(entity)) {
    description.transform_comp =
        coordinator->GetComponent<TransformationComponent>(entity);
  } else {
    description.transform_comp = std::nullopt;
  };
  if (coordinator->HasComponent<PixmapComponent>(entity)) {
    description.pixmap_comp =
        coordinator->GetComponent<PixmapComponent>(entity);
  } else {
    description.pixmap_comp = std::nullopt;
  };
  if (coordinator->HasComponent<MotionComponent>(entity)) {
    description.motion_comp =
        coordinator->GetComponent<MotionComponent>(entity);
  } else {
    description.motion_comp = std::nullopt;
  };
  if (coordinator->HasComponent<CollisionComponent>(entity)) {
    description.collision_comp =
        coordinator->GetComponent<CollisionComponent>(entity);
  } else {
    description.collision_comp = std::nullopt;
  };
  return description;
}

void SerializationSystem::LoadToJson(Room room) {

}

Room SerializationSystem::LoadFromJson(int id) {
  return Room();
}


