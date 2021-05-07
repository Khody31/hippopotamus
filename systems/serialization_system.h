#pragma  once

#include "engine/system.h"
#include "core/room.h"
#include "engine/coordinator.h"
#include "core/spawner.h"

class SerializationSystem : public System {
 public:
  void Deserialize(Coordinator* coordinator, Spawner* spawner, int32_t id);
  void Serialize(Coordinator* coordinator);

  void SetDoors(std::array<Entity, 4> doors);

 private:
  void UpdateDoors(Coordinator* coordinator);
  static EntityDescription CreateDescription(Entity entity,
                                             Coordinator* coordinator);

  static Room LoadRoomFromJson(int32_t id);
  static EntityDescription LoadFromJson(const QJsonObject& object);
  static QVector2D LoadFromJson(const QJsonArray& object);

  static void LoadToJson(const Room& room);
  static QJsonArray LoadToJson(const QVector2D& vector);
  static QJsonObject LoadToJson(const EntityDescription& description);

 private:
  int32_t current_room_id_ = 0;
  std::array<Entity, 4> doors_{};
};
