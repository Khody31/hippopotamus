#include "serialization_system.h"

#include "core/constants.h"
#include "core/utility.h"
#include "components/components.h"

SerializationSystem::SerializationSystem(Coordinator* coordinator,
                                         Spawner* spawner) :
    coordinator_(coordinator),
    spawner_(spawner),
    current_room_id_(0),
    doors_() {}

void SerializationSystem::Serialize() {
  RoomDescription current_room{current_room_id_};
  for (int i = 0; i < 4; ++i) {
    current_room.connected_rooms[i] =
        coordinator_->GetComponent<DoorComponent>(doors_[i]).room_id;
  }

  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;
    current_room.descriptions.push_back(CreateDescription(entity));
    coordinator_->DestroyEntity(entity);
  }

  utility::LoadRoomToJson(current_room);
}

void SerializationSystem::Deserialize(int32_t id) {
  current_room_id_ = id;
  RoomDescription next_room = utility::LoadRoomFromJson(id);
  for (const auto& description : next_room.descriptions) {
    spawner_->CreateEntity(description.type, description.position);
  }

  std::array<int32_t, 4> connected_rooms = next_room.connected_rooms;
  for (int i = 0; i < 4; ++i) {
    coordinator_->GetComponent<DoorComponent>(doors_[i]).room_id
        = connected_rooms[i];
  }

  UpdateDoors(coordinator_);
}

EntityDescription SerializationSystem::CreateDescription(Entity entity) {
  auto transform_component =
      coordinator_->GetComponent<TransformationComponent>(entity);
  auto serialization_component =
      coordinator_->GetComponent<SerializationComponent>(entity);
  return EntityDescription(serialization_component.type,
                           transform_component.pos);
}

void SerializationSystem::UpdateDoors(Coordinator* coordinator) {
  for (int i = 0; i < 4; ++i) {
    uint32_t door = doors_[i];
    if (coordinator->GetComponent<DoorComponent>(door).room_id == -1) {
      if (coordinator->HasComponent<PixmapComponent>(door)) {
        coordinator->RemoveComponent<PixmapComponent>(door);
      }
      if (coordinator->HasComponent<CollisionComponent>(door)) {
        coordinator->RemoveComponent<CollisionComponent>(door);
      }
    } else {
      QVector2D size = (i % 2 == 1) ? constants::kVerticalDoorSize
                                    : constants::kHorizontalDoorSize;
      if (!coordinator->HasComponent<PixmapComponent>(door)) {
        QPixmap pixmap(":/textures/player.png");
        coordinator->AddComponent<PixmapComponent>(
            door,
            PixmapComponent{pixmap, size});
      }
      if (!coordinator->HasComponent<CollisionComponent>(door)) {
        coordinator->AddComponent<CollisionComponent>(
            door, CollisionComponent{
                0, 0, size});
      }
    }
  }
}
void SerializationSystem::SetDoors(std::array<Entity, 4> doors) {
  doors_ = doors;
}


