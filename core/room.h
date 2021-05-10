#pragma once

#include "entity_description.h"
#include "engine/types.h"

#include <vector>
#include <array>

class Room {
 public:
  explicit Room(int32_t id);

  int32_t GetId() const;

  const std::array<int32_t, 4>& GetConnectedRooms() const;
  void SetConnectedRooms(const std::array<int32_t, 4>& rooms);

  void AddDescription(const EntityDescription& description);
  const std::vector<EntityDescription>& GetDescriptions() const;

 private:
  int32_t id_;
  std::vector<EntityDescription> descriptions_;
  std::array<int32_t, 4> connected_rooms_{};
};
