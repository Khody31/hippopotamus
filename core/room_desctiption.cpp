#include "room_desctiption.h"

RoomDescription::RoomDescription(int32_t id) : id_(id) {}

void RoomDescription::AddDescription(const EntityDescription& description) {
  descriptions_.push_back(description);
}

int32_t RoomDescription::GetId() const {
  return id_;
}

const std::vector<EntityDescription>& RoomDescription::GetDescriptions() const {
  return descriptions_;
}

const std::array<int32_t, 4>& RoomDescription::GetConnectedRooms() const {
  return connected_rooms_;
}

void RoomDescription::SetConnectedRooms(const std::array<int32_t, 4>& rooms) {
  connected_rooms_ = rooms;
}
