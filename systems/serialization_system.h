#pragma  once

#include "engine/system.h"
#include "core/room.h"
#include "engine/coordinator.h"
#include "core/spawner.h"

class SerializationSystem : public System {
 public:
  SerializationSystem(Coordinator* coordinator, Spawner* spawner);

  void Serialize();
  void Deserialize(int32_t id);

  void SetDoors(std::array<Entity, 4> doors);

 private:
  void UpdateDoors(Coordinator* coordinator);
  EntityDescription CreateDescription(Entity entity);

  Room LoadRoomFromJson(int32_t id);
  EntityDescription LoadFromJson(const QJsonObject& object);
  QVector2D LoadFromJson(const QJsonArray& object);

  void LoadToJson(const Room& room);
  QJsonArray LoadToJson(const QVector2D& vector);
  QJsonObject LoadToJson(const EntityDescription& description);

 private:
  Coordinator* coordinator_;
  Spawner* spawner_;

  int32_t current_room_id_;
  std::array<Entity, 4> doors_;
};
