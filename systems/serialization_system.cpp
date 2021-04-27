#include "serialization_system.h"

void SerializationSystem::Serialize(Coordinator* coordinator) {
  Room current_room;
  for (const auto& entity : entities_) {
    current_room.AddDescription(CreateDescription(entity, coordinator));
    coordinator->DestroyEntity(entity);
  }
  LoadToJson(current_room);
}

void SerializationSystem::Deserialize(Coordinator* coordinator, int id) {
  Room next_room = LoadFromJson(id);
  for(const auto& description : next_room.GetDescriptions()) {
    CreateEntity(description, coordinator);
  }
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

void SerializationSystem::CreateEntity(const EntityDescription& description,
                                       Coordinator* coordinator) {
  Entity entity = coordinator->CreateEntity();
  if(description.transform_comp) {
    coordinator->AddComponent(entity, description.transform_comp);
  }
  if(description.motion_comp) {
    coordinator->AddComponent(entity, description.motion_comp);
  }
  if(description.pixmap_comp) {
    coordinator->AddComponent(entity, description.pixmap_comp);
  }
  if(description.collision_comp) {
    coordinator->AddComponent(entity, description.collision_comp);
  }
}


