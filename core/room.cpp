#include "room.h"

void Room::AddDescription(EntityDescription description) {
  descriptions_.push_back(description);
}
int Room::GetId() {
  return id_;
}
const std::vector<EntityDescription>& Room::GetDescriptions() const {
  return descriptions_;
}
