#include <QSize>
#include <QFile>
#include <QVector2D>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>

#include <fstream>

#include "utility.h"
#include "connector.h"
#include "constants.h"

QPoint utility::GameToWidgetCoord(const QVector2D& coord,
                                  const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                    static_cast<float>(scene_size.height()));

  QVector2D inverted(coord.x(), -coord.y());
  QVector2D result =
      (inverted + constants::kMaxGameCoordinates) * size_vector
          / (2 * constants::kMaxGameCoordinates);
  return {static_cast<int>(result.x()), static_cast<int>(result.y())};
}

QVector2D utility::WidgetToGameCoord(const QPoint& coord,
                                     const QSize& scene_size) {
  QVector2D size_vector = QVector2D(static_cast<float>(scene_size.width()),
                                    static_cast<float>(scene_size.height()));
  QVector2D result =
      QVector2D(coord) * constants::kMaxGameCoordinates * 2
          / size_vector - constants::kMaxGameCoordinates;
  result.setY(-result.y());
  return result;
}

QString GetRoomPath(int32_t id) {
  return "../resources/rooms/room" + QString::number(id) + ".json";
}

RoomDescription utility::LoadRoomFromJson(int32_t id) {
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

void utility::LoadRoomToJson(const RoomDescription& room) {
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

  QString file_path = GetRoomPath(room.id);
  if (!QFile::exists(file_path)) {
    std::ofstream file_stream("../resources/rooms/room" + std::to_string(room.id) + ".json");
    file_stream.close();
  }

  QFile file(GetRoomPath(room.id));
  file.open(QIODevice::WriteOnly);
  file.write(QJsonDocument(object).toJson());
  file.close();
}

QJsonObject utility::ConvertToJson(
    const EntityDescription& description) {
  QJsonObject object;
  object.insert("type", static_cast<int>(description.type));
  object.insert("pos", ConvertToJson(description.pos));
  return object;
}

QJsonArray utility::ConvertToJson(const QVector2D& vector) {
  QJsonArray array;
  array.append(vector.x());
  array.append(vector.y());
  return array;
}

QVector2D utility::ConvertFromJson(const QJsonArray& object) {
  QVector2D result;
  result[0] = static_cast<float>(object[0].toDouble());
  result[1] = static_cast<float>(object[1].toDouble());
  return result;
}

EntityDescription utility::ConvertFromJson(
    const QJsonObject& object) {
  EntityDescription description;
  description.type = static_cast<EntityType>(object["type"].toInt());
  description.pos = ConvertFromJson(object["pos"].toArray());
  return description;
}

double utility::CalculateAngle(QVector2D first_vec, QVector2D second_vec) {
  double scalar_product = first_vec.x() * second_vec.x() + first_vec.y() *
      second_vec.y();
  return scalar_product / (first_vec.length() * second_vec.length());
}

void utility::TurnVector(QVector2D* vec) {
  float x_coordinate = vec->x();
  vec->setX(vec->y());
  vec->setY(-1 * x_coordinate);
}
