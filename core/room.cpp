#include "room.h"

void Room::AddDescription(const EntityDescription& description) {
  descriptions_.push_back(description);
}

int Room::GetId() const {
  return id_;
}

const std::vector<EntityDescription>& Room::GetDescriptions() const {
  return descriptions_;
}
