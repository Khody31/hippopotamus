#pragma  once

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "components/components.h"
#include "engine/coordinator.h"
#include "core/descriptions.h"
#include "core/spawner.h"

class SerializationSystem : public System {
 public:
  SerializationSystem(Coordinator* coordinator,
                      Spawner* spawner,
                      Entity* player);

  void Serialize();
  void Deserialize(const DoorComponent& door);

 private:
  EntityDescription CreateDescription(Entity entity);

  Coordinator* coordinator_;
  Spawner* spawner_;
  Entity* player_;
  RoomDescription current_room_;
};
