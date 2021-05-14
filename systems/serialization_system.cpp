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
    doors_() {}

QString GetRoomPath(int32_t id) {
  return "../res/rooms/room" + QString::number(id) + ".json";
}

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

  LoadToJson(current_room);
}

void SerializationSystem::Deserialize(int32_t id) {
  current_room_id_ = id;
  RoomDescription next_room = LoadRoomFromJson(id);
  for (const auto& description : next_room.descriptions) {
    spawner_->CreateEntity(description.type, description.pos);
  }

  std::array<int32_t, 4> connected_rooms = next_room.connected_rooms;
  for (int i = 0; i < 4; ++i) {
    coordinator_->GetComponent<DoorComponent>(doors_[i]).room_id
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

RoomDescription SerializationSystem::LoadRoomFromJson(int32_t id) {
  QFile file(GetRoomPath(id));
  file.open(QIODevice::ReadOnly);
  QJsonObject json_object =
      QJsonDocument::fromJson(file.readAll()).object();
  file.close();

  RoomDescription result{json_object["id"].toInt()};
  QJsonArray entity_descriptions = json_object["entities"].toArray();
  for (auto&& entity_description : entity_descriptions) {
    EntityDescription description =
        ConvertFromJson(entity_description.toObject());
    result.descriptions.push_back(description);
  }

  QJsonArray rooms = json_object["rooms"].toArray();
  for (int i = 0; i < 4; ++i) {
    result.connected_rooms[i] = rooms[i].toInt();
  }
  return result;
}

void SerializationSystem::LoadToJson(const RoomDescription& room) {
  QJsonObject object;
  object.insert("id", room.id);

  QJsonArray entities;
  for (const auto& description : room.descriptions) {
    entities.append(QJsonObject(ConvertToJson(description)));
  }
  object.insert("entities", entities);

  QJsonArray connected_rooms;
  for (int32_t room_id : room.connected_rooms) {
    connected_rooms.append(room_id);
  }
  object.insert("rooms", connected_rooms);

  QFile file(GetRoomPath(room.id));
  file.open(QIODevice::WriteOnly);
  file.write(QJsonDocument(object).toJson());
  file.close();
}

QJsonObject SerializationSystem::ConvertToJson(
    const EntityDescription& description) {
  QJsonObject object;
  object.insert("type", static_cast<int>(description.type));
  object.insert("pos", ConvertToJson(description.pos));
  return object;
}

QJsonArray SerializationSystem::ConvertToJson(const QVector2D& vector) {
  QJsonArray array;
  array.append(vector.x());
  array.append(vector.y());
  return array;
}

QVector2D SerializationSystem::ConvertFromJson(const QJsonArray& object) {
  QVector2D result;
  result[0] = static_cast<float>(object[0].toDouble());
  result[1] = static_cast<float>(object[1].toDouble());
  return result;
}

EntityDescription SerializationSystem::ConvertFromJson(
    const QJsonObject& object) {
  EntityDescription description;
  description.type = static_cast<EntityType>(object["type"].toInt());
  description.pos = ConvertFromJson(object["pos"].toArray());
  return description;
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
                0, 0, size});
      }
    }
  }
}
void SerializationSystem::SetDoors(std::array<Entity, 4> doors) {
  doors_ = doors;
}


