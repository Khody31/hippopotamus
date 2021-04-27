#pragma  once

#include "engine/system.h"
#include "core/room.h"
#include "engine/coordinator.h"

class SerializationSystem : public System {
 public:
  void Deserialize(Coordinator* coordinator, int id);
  void Serialize(Coordinator* coordinator);
 private:
  void LoadToJson(Room room);
  Room LoadFromJson(int id);

  EntityDescription CreateDescription(Entity entity, Coordinator* coordinator);
  void CreateEntity(const EntityDescription& description, Coordinator*
  coordinator);
};
