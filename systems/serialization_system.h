#pragma  once

#include "engine/system.h"
#include "core/room.h"

class SerializationSystem : public System {
 public:
  void Deserialize(Coordinator* coordinator, int id);
  void DestroyAllEntities();
  void Serialize();
 private:
  void LoadToJson(Room room);
  Room LoadFromJson(int id);

};
