#include "serialization_system.h"

#include "core/constants.h"
#include "utilities/conversion.h"
#include "components/components.h"

SerializationSystem::SerializationSystem(Coordinator* coordinator,
                                         Spawner* spawner,
                                         Entity* player) :
    coordinator_(coordinator),
    spawner_(spawner),
    player_(player),
    current_room_() {}

EntityDescription SerializationSystem::CreateDescription(Entity entity) {
  auto transform = coordinator_->GetComponent<TransformationComponent>(entity);
  auto serialization =
      coordinator_->GetComponent<SerializationComponent>(entity);

  return {serialization.type, transform.position};
}

void SerializationSystem::Serialize() {
  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;
    current_room_.descriptions.push_back(CreateDescription(entity));
    coordinator_->DestroyEntity(entity);
  }

  utility::LoadRoomToJson(current_room_);
}

void SerializationSystem::Deserialize(const DoorComponent& door) {
  coordinator_->GetComponent<TransformationComponent>(*player_).position =
      door.player_position;

  current_room_ = utility::LoadRoomFromJson(door.room_id);
  for (const auto&[type, position] : current_room_.descriptions) {
    spawner_->CreateEntity(type, position);
  }
  current_room_.descriptions.clear();

  spawner_->CreateDoors(current_room_.connected_rooms);
}
