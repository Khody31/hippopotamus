#include "serialization_system.h"

#include "core/utility.h"
#include "core/constants.h"
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

  LoadCurrentRoomToJson();
}

void SerializationSystem::Deserialize(const DoorComponent& door) {
  coordinator_->GetComponent<TransformationComponent>(*player_).position =
      door.player_position;

  LoadCurrentRoomFromJson(door.room_id);
  for (const auto&[type, position] : current_room_.descriptions) {
    spawner_->CreateEntity(type, position);
  }
  current_room_.descriptions.clear();

  spawner_->CreateDoors(current_room_.connected_rooms);
}

void SerializationSystem::LoadCurrentRoomFromJson(int32_t id) {
  QFile file(utility::GetRoomPath(id));
  file.open(QIODevice::ReadOnly);
  QJsonObject json_object = QJsonDocument::fromJson(file.readAll()).object();
  file.close();

  current_room_.id = json_object["id"].toInt();
  current_room_.descriptions.clear();

  for (auto&& entity_description : json_object["entities"].toArray()) {
    QJsonObject object = entity_description.toObject();
    QJsonArray array = object["position"].toArray();

    EntityType type = static_cast<EntityType>(object["type"].toInt());
    QVector2D position(static_cast<float>(array[0].toDouble()),
                       static_cast<float>(array[1].toDouble()));

    current_room_.descriptions.push_back({type, position});
  }

  QJsonArray rooms = json_object["rooms"].toArray();
  for (int i = 0; i < 4; ++i) {
    current_room_.connected_rooms[i] = rooms[i].toInt();
  }
}

void SerializationSystem::LoadCurrentRoomToJson() {
  QJsonObject object;
  object.insert("id", current_room_.id);

  QJsonArray entities;
  for (const auto& description : current_room_.descriptions) {
    QJsonObject entity_object;
    entity_object.insert("type", static_cast<int>(description.type));

    QJsonArray array;
    array.append(description.position.x());
    array.append(description.position.y());

    entity_object.insert("position", array);
    entities.append(entity_object);
  }
  object.insert("entities", entities);

  QJsonArray connected_rooms;
  for (int32_t room_id : current_room_.connected_rooms) {
    connected_rooms.append(room_id);
  }
  object.insert("rooms", connected_rooms);

  QFile file(utility::GetRoomPath(current_room_.id));
  file.open(QIODevice::WriteOnly);
  file.write(QJsonDocument(object).toJson());
  file.close();
}
