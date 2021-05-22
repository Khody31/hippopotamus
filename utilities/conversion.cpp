#include "conversion.h"

#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>

#include <algorithm>

namespace utility {

QString GetRoomPath(int32_t id) {
  return "rooms/room" + QString::number(id) + ".json";
}

RoomDescription LoadRoomFromJson(int32_t id) {
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

void LoadRoomToJson(const RoomDescription& room) {
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

  QDir dir;
  if (!dir.exists("rooms")) {
    dir.mkdir("rooms");
  }

  QFile file(GetRoomPath(room.id));
  file.open(QIODevice::WriteOnly);
  file.write(QJsonDocument(object).toJson());
  file.close();
}

QJsonObject ConvertToJson(const EntityDescription& description) {
  QJsonObject object;
  object.insert("type", static_cast<int>(description.type));
  object.insert("position", ConvertToJson(description.position));
  return object;
}

QJsonArray ConvertToJson(const QVector2D& vector) {
  QJsonArray array;
  array.append(vector.x());
  array.append(vector.y());
  return array;
}

QVector2D ConvertFromJson(const QJsonArray& object) {
  QVector2D result;
  result[0] = static_cast<float>(object[0].toDouble());
  result[1] = static_cast<float>(object[1].toDouble());
  return result;
}

EntityDescription ConvertFromJson(const QJsonObject& object) {
  return EntityDescription(
      static_cast<EntityType>(object["type"].toInt()),
      ConvertFromJson(object["position"].toArray()));
}

}  // namespace utility
