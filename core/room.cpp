#include "room.h"

void Room::AddDescription(const EntityDescription& description) {
  descriptions_.push_back(description);
}
