#pragma once

#include "entity_description.h"

class Room {
 public:
  void AddDescription(const EntityDescription& description);
  const std::vector<EntityDescription>& GetDescriptions();
 private:
  int id_;
  std::vector<EntityDescription> descriptions_;
};
