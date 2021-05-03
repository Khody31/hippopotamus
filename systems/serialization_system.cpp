#include "serialization_system.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

void SerializationSystem::Serialize(Coordinator* coordinator, int cur_room_id) {
  Room current_room(cur_room_id);
  for (const auto& entity : entities_) {
    qDebug() << entity;
    current_room.AddDescription(CreateDescription(entity, coordinator));
    coordinator->DestroyEntity(entity);
  }
  LoadToJson(current_room);
}

void SerializationSystem::Deserialize(Coordinator* coordinator,
                                      int id,
                                      Spawner* spawner) {
  Room next_room = LoadFromJson(id);
  for (const auto& description : next_room.GetDescriptions()) {
    spawner->CreateEntity(description.type, description.pos);
  }
}

EntityDescription SerializationSystem::CreateDescription(Entity entity,
                                                         Coordinator* coordinator) {
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
  QJsonObject json_object = QJsonDocument::fromJson(
      file.readAll()).object();
  file.close();

  Room result(json_object["id"].toInt());
  QJsonArray entity_descriptions = json_object["entities"].toArray();
  for (int i = 0; i < entity_descriptions.size(); ++i) {
    EntityDescription description =
        LoadDescription(entity_descriptions[i].toObject());
    result.AddDescription(description);
  }

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

  QFile file(QStringLiteral("room0.json"));
  file.open(QIODevice::WriteOnly);
  file.write(QJsonDocument(object).toJson());
  file.close();
}

QJsonObject SerializationSystem::LoadToJson(const EntityDescription& description) {
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

EntityDescription SerializationSystem::LoadDescription(const QJsonObject& object) {
  EntityDescription description;
  description.type = static_cast<EntityType>(object["type"].toInt());
  description.pos = LoadFromJson(object["pos"].toArray());
  return description;
}