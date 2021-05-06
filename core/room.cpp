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

std::array<uint32_t, 4> Room::GetConnectedRooms() const {
  return connected_rooms_;
}

void Room::SetConnectedRooms(const std::array<uint32_t, 4>& rooms) {
  connected_rooms_ = rooms;
}
