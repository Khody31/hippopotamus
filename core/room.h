#pragma once

#include "entity_description.h"

class Room {
 public:
  void AddDescription(const EntityDescription& description);
 private:
  int id_;
  std::vector<EntityDescription> descriptions_;
};
