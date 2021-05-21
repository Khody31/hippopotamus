#pragma once

#include "core/descriptions.h"
#include <QVector2D>

namespace json {

RoomDescription LoadRoomFromJson(int32_t id);
EntityDescription ConvertFromJson(const QJsonObject& object);
QVector2D ConvertFromJson(const QJsonArray& object);

void LoadRoomToJson(const RoomDescription& room);
QJsonArray ConvertToJson(const QVector2D& vector);
QJsonObject ConvertToJson(const EntityDescription& description);

}  // namespace json