#pragma once

#include "entity_description.h"

class Room {
 public:
  Room() = default;
  explicit Room(int id) : id_(id) {}

  int GetId();
  void AddDescription(EntityDescription);
  const std::vector<EntityDescription>& GetDescriptions() const;
 private:
  int id_;
  std::vector<EntityDescription> descriptions_;
};
