#include "serialization_system.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

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
  return description;
}

void SerializationSystem::CreateEntity(const EntityDescription& description,
                                       Coordinator* coordinator) {
  Entity entity = coordinator->CreateEntity();
}

Room SerializationSystem::LoadFromJson(int id) {
  QFile file(":map/room" + QString::number(id));
  file.open(QIODevice::ReadOnly);
  QJsonObject json_object = QJsonDocument::fromJson(
      file.readAll()).object();

  Room result(json_object["id"].toInt());
  QJsonArray entity_descriptions = json_object["entities"].toArray();
  for (int i = 0; i < entity_descriptions.size(); ++i) {
    EntityDescription description =
        LoadDescription(entity_descriptions[i].toObject());
    result.AddDescription(description);
  }

  return result;
}

void SerializationSystem::LoadToJson(Room room) {
  QJsonObject object;
  object.insert("id", room.GetId());
  QJsonArray entities;

  for (const auto& description : room.GetDescriptions()) {
    entities.append(QJsonObject(LoadToJson(description)));
  }

  object.insert("entities", entities);

  QFile file(":map/room" + QString::number(room.GetId()));
  file.open(QIODevice::WriteOnly);
  file.write(QJsonDocument(object).toJson());
}

QJsonObject SerializationSystem::LoadToJson(const EntityDescription& description) {
  QJsonObject object;

  object.insert("type", static_cast<int>(description.type));
  object.insert("pos", LoadToJson(description.pos));

  return object;
}

auto SerializationSystem::LoadVec2D(QJsonArray object) {
  QVector2D result;
  result[0] = static_cast<float>(object[0].toDouble());
  result[1] = static_cast<float>(object[1].toDouble());
  return result;
}

QJsonArray SerializationSystem::LoadToJson(const QVector2D &vector) {
  QJsonArray array;
  array.append(vector.x());
  array.append(vector.y());
  return array;
}

EntityDescription SerializationSystem::LoadDescription(QJsonObject object) {
    EntityDescription description;
    description.type = static_cast<EntityType>(object["type"].toInt());
    description.pos = LoadVec2D(object["pos"].toArray());
    return description;
}
