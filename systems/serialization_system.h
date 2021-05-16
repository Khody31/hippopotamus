#pragma  once

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "engine/coordinator.h"
#include "core/descriptions.h"
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

 private:
  Coordinator* coordinator_;
  Spawner* spawner_;

  int32_t current_room_id_;
  std::array<Entity, 4> doors_;
};
