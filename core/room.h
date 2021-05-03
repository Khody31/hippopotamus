#pragma once

#include "entity_description.h"

#include <vector>

class Room {
 public:
  Room() = default;
  explicit Room(int id) : id_(id) {}
  int GetId() const;
  void AddDescription(const EntityDescription& description);
  const std::vector<EntityDescription>& GetDescriptions() const;
 private:
  int id_;
  std::vector<EntityDescription> descriptions_;
};
