#include "serialization_system.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "core/constants.h"

SerializationSystem::SerializationSystem(Coordinator* coordinator,
                                         Spawner* spawner) :
    coordinator_(coordinator),
    spawner_(spawner),
    current_room_id_(0),
    doors_() {

}

QString GetRoomPath(int32_t id) {
  return "../res/rooms/room" + QString::number(id) + ".json";
}

void SerializationSystem::Serialize() {
  Room current_room(current_room_id_);
  std::array<int32_t, 4> connected_rooms_{};
  for (int i = 0; i < 4; ++i) {
    connected_rooms_[i] =
        coordinator_->GetComponent<DoorComponent>(doors_[i]).next_room_id;
  }
  current_room.SetConnectedRooms(connected_rooms_);

  auto it = entities_.begin();
  while (it != entities_.end()) {
    Entity entity = *it++;
    current_room.AddDescription(CreateDescription(entity));
    coordinator_->DestroyEntity(entity);
  }

  LoadToJson(current_room);
}

void SerializationSystem::Deserialize(int32_t id) {
  current_room_id_ = id;
  Room next_room = LoadRoomFromJson(id);
  for (const auto& description : next_room.GetDescriptions()) {
    spawner_->CreateEntity(description.type, description.pos);
  }

  std::array<int32_t, 4> connected_rooms = next_room.GetConnectedRooms();
  for (int i = 0; i < 4; ++i) {
    coordinator_->GetComponent<DoorComponent>(doors_[i]).next_room_id
        = connected_rooms[i];
  }

  UpdateDoors(coordinator_);
}

EntityDescription SerializationSystem::CreateDescription(Entity entity) {
  EntityDescription description;
  auto transform_component =
      coordinator_->GetComponent<TransformationComponent>(entity);
  auto serialization_component =
      coordinator_->GetComponent<SerializationComponent>(entity);
  description.pos = transform_component.pos;
  description.type = serialization_component.type;
  return description;
}

Room SerializationSystem::LoadRoomFromJson(int32_t id) {
  QFile file(GetRoomPath(id));
  file.open(QIODevice::ReadOnly);
  QJsonObject json_object =
      QJsonDocument::fromJson(file.readAll()).object();
  file.close();

  Room result(json_object["id"].toInt());
  QJsonArray entity_descriptions = json_object["entities"].toArray();
  for (auto&& entity_description : entity_descriptions) {
    EntityDescription description = LoadFromJson(entity_description.toObject());
    result.AddDescription(description);
  }

  QJsonArray rooms = json_object["rooms"].toArray();
  std::array<int32_t, 4> connected_rooms{};
  for (int i = 0; i < 4; ++i) {
    connected_rooms[i] = rooms[i].toInt();
  }
  result.SetConnectedRooms(connected_rooms);

  return result;
}

void SerializationSystem::LoadToJson(const Room& room) {
  QJsonObject object;
  object.insert("id", room.GetId());

  QJsonArray entities;
  for (const auto& description : room.GetDescriptions()) {
    entities.append(QJsonObject(LoadToJson(description)));
  }
  object.insert("entities", entities);

  QJsonArray connected_rooms;
  for (int32_t room_id : room.GetConnectedRooms()) {
    connected_rooms.append(room_id);
  }
  object.insert("rooms", connected_rooms);

  QFile file(GetRoomPath(room.GetId()));
  file.open(QIODevice::WriteOnly);
  file.write(QJsonDocument(object).toJson());
  file.close();
}

QJsonObject SerializationSystem::LoadToJson(
    const EntityDescription& description) {
  QJsonObject object;
  object.insert("type", static_cast<int>(description.type));
  object.insert("pos", LoadToJson(description.pos));
  return object;
}

QJsonArray SerializationSystem::LoadToJson(const QVector2D& vector) {
  QJsonArray array;
  array.append(vector.x());
  array.append(vector.y());
  return array;
}

QVector2D SerializationSystem::LoadFromJson(const QJsonArray& object) {
  QVector2D result;
  result[0] = static_cast<float>(object[0].toDouble());
  result[1] = static_cast<float>(object[1].toDouble());
  return result;
}

EntityDescription SerializationSystem::LoadFromJson(
    const QJsonObject& object) {
  EntityDescription description;
  description.type = static_cast<EntityType>(object["type"].toInt());
  description.pos = LoadFromJson(object["pos"].toArray());
  return description;
}

void SerializationSystem::UpdateDoors(Coordinator* coordinator) {
  for (int i = 0; i < 4; ++i) {
    uint32_t door = doors_[i];
    if (coordinator->GetComponent<DoorComponent>(door).next_room_id == -1) {
      if (coordinator->HasComponent<PixmapComponent>(door)) {
        coordinator->RemoveComponent<PixmapComponent>(door);
      }
      if (coordinator->HasComponent<CollisionComponent>(door)) {
        coordinator->RemoveComponent<CollisionComponent>(door);
      }
    } else {
      QVector2D size = (i % 2 == 1) ? game_constants::kVerticalDoorSize
                                    : game_constants::kHorizontalDoorSize;
      if (!coordinator->HasComponent<PixmapComponent>(door)) {
        QPixmap pixmap(":/textures/player.png");
        coordinator->AddComponent<PixmapComponent>(
            door,
            PixmapComponent{pixmap, size});
      }
      if (!coordinator->HasComponent<CollisionComponent>(door)) {
        coordinator->AddComponent<CollisionComponent>(
            door, CollisionComponent{
                0, 0, size, CollisionType::kRoomChanging});
      }
    }
  }
}
void SerializationSystem::SetDoors(std::array<Entity, 4> doors) {
  doors_ = doors;
}


