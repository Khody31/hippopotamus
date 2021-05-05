#include "serialization_system.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

void SerializationSystem::Serialize(Coordinator* coordinator, uint32_t cur_room_id,
                                    const std::array<uint32_t, 4>& connected_rooms) {
  Room current_room(cur_room_id);
  current_room.SetConnectedRooms(connected_rooms);
  for (const auto& entity : entities_) {
    current_room.AddDescription(CreateDescription(entity, coordinator));
    coordinator->DestroyEntity(entity);
  }
  LoadToJson(current_room);
}

void SerializationSystem::Deserialize(Coordinator* coordinator,
                                      uint32_t id,
                                      Spawner* spawner,
                                      std::array<uint32_t, 4>* connected_rooms) {
  Room next_room = LoadFromJson(id);
  for (const auto& description : next_room.GetDescriptions()) {
    spawner->CreateEntity(description.type, description.pos);
  }
  *connected_rooms = next_room.GetConnectedRooms();
}

EntityDescription SerializationSystem::CreateDescription(
    Entity entity, Coordinator* coordinator) {
  EntityDescription description;
  auto transform_component =
      coordinator->GetComponent<TransformationComponent>(entity);
  auto serialization_component =
      coordinator->GetComponent<SerializationComponent>(entity);
  description.pos = transform_component.pos;
  description.type = serialization_component.type;
  return description;
}

Room SerializationSystem::LoadFromJson(int id) {
  QFile file("room" + QString::number(id) + ".json");
  file.open(QIODevice::ReadOnly);
  QJsonObject json_object =
      QJsonDocument::fromJson(file.readAll()).object();
  file.close();

  Room result(json_object["id"].toInt());
  QJsonArray entity_descriptions = json_object["entities"].toArray();
  for (int i = 0; i < entity_descriptions.size(); ++i) {
    EntityDescription description =
        LoadDescription(entity_descriptions[i].toObject());
    result.AddDescription(description);
  }

  QJsonArray rooms = json_object["rooms"].toArray();
  std::array<uint32_t, 4> connected_rooms;
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
  for (uint32_t room_id : room.GetConnectedRooms()) {
    connected_rooms.append(static_cast<int>(room_id));
  }
  object.insert("rooms", connected_rooms);

  QFile file("room" + QString::number(room.GetId()) + ".json");
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

EntityDescription SerializationSystem::LoadDescription(
    const QJsonObject& object) {
  EntityDescription description;
  description.type = static_cast<EntityType>(object["type"].toInt());
  description.pos = LoadFromJson(object["pos"].toArray());
  return description;
}
