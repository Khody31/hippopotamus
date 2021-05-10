#include "room.h"

Room::Room(int32_t id) : id_(id) {}

void Room::AddDescription(const EntityDescription& description) {
  descriptions_.push_back(description);
}

int32_t Room::GetId() const {
  return id_;
}

const std::vector<EntityDescription>& Room::GetDescriptions() const {
  return descriptions_;
}

const std::array<int32_t, 4>& Room::GetConnectedRooms() const {
  return connected_rooms_;
}

void Room::SetConnectedRooms(const std::array<int32_t, 4>& rooms) {
  connected_rooms_ = rooms;
}
