#pragma  once

#include "engine/system.h"
#include "core/room.h"
#include "engine/coordinator.h"
#include "core/spawner.h"

class SerializationSystem : public System {
 public:
  static void Deserialize(Coordinator* coordinator, int id, Spawner* spawner);
  void Serialize(Coordinator* coordinator, int current_room_id);
 private:
  static EntityDescription CreateDescription(Entity entity,
                                             Coordinator* coordinator);

  static void LoadToJson(const Room& room);
  static Room LoadFromJson(int id);

  static EntityDescription LoadDescription(const QJsonObject& object);
  static QVector2D LoadFromJson(const QJsonArray& object);

  static QJsonArray LoadToJson(const QVector2D& vector);
  static QJsonObject LoadToJson(const EntityDescription& description);
};
