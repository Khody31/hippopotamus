#pragma once

#include <QVector2D>
#include "descriptions.h"

namespace utility {

// coordinates-connected utilities
QPoint GameToWidgetCoord(const QVector2D& coord, const QSize& scene_size);
QVector2D WidgetToGameCoord(const QPoint& coord, const QSize& scene_size);


// json-connected utilities
RoomDescription LoadRoomFromJson(int32_t id);
EntityDescription ConvertFromJson(const QJsonObject& object);
QVector2D ConvertFromJson(const QJsonArray& object);

void LoadRoomToJson(const RoomDescription& room);
QJsonArray ConvertToJson(const QVector2D& vector);
QJsonObject ConvertToJson(const EntityDescription& description);

}  // namespace utility
