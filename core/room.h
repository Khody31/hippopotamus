#pragma once

#include "entity_description.h"
#include "engine/types.h"

#include <vector>
#include <array>

class Room {
 public:
  Room() = default;
  explicit Room(int id) : id_(id) {}

  int GetId() const;

  std::array<uint32_t, 4> GetConnectedRooms() const;
  void SetConnectedRooms(const std::array<uint32_t, 4>& rooms);

  void AddDescription(const EntityDescription& description);
  const std::vector<EntityDescription>& GetDescriptions() const;

 private:
  int id_;
  std::vector<EntityDescription> descriptions_;
  std::array<uint32_t, 4> connected_rooms_{};
};
