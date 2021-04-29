#pragma  once

#include "engine/system.h"
#include "core/room.h"

class SerializationSystem : public System {
 public:
  void Deserialize(Coordinator* coordinator, int id);
  void Serialize();
 private:
  static void LoadToJson(Room room);
  static Room LoadFromJson(int id);
  static EntityDescription LoadDescription(QJsonObject object);
  static auto LoadVec2D(QJsonArray object);
  static QJsonArray LoadToJson(const QVector2D& vector);
  static QJsonObject LoadToJson(const EntityDescription& description);
};
