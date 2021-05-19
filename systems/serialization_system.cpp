#include <iostream>
#include "serialization_system.h"

#include "core/constants.h"
#include "components/components.h"

SerializationSystem::SerializationSystem(Coordinator* coordinator,
                                         Spawner* spawner) :
    coordinator_(coordinator),
    spawner_(spawner),
    current_room_id_(0),
    doors_() {}

QString GetRoomPath(int32_t id) {
  return "../resources/rooms/room" + QString::number(id) + ".json";
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

  doors_ = spawner_->CreateDoors(next_room.connected_rooms);
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
