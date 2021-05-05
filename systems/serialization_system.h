#pragma  once

#include "engine/system.h"
#include "core/room.h"
#include "engine/coordinator.h"
#include "core/spawner.h"

class SerializationSystem : public System {
 public:
  static void Deserialize(Coordinator* coordinator,
                          uint32_t id, Spawner* spawner,
                          std::array<uint32_t, 4>* connected_rooms);
  void Serialize(Coordinator* coordinator,
                 uint32_t current_room_id,
                 const std::array<uint32_t, 4>& connected_rooms);
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
