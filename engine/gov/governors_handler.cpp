#include "governors_handler.h"

void GovernorsHandler::AddGovernor(Governor* governor, uint64_t type_id) {
  if (type_id >= governors_.size()) {
    throw std::logic_error("(GovernorsHandler::AddGovernor) No such component type");
  }
  if (governors_[type_id]) {
    throw std::logic_error("(GovernorsHandler::AddGovernor) Governor is already set");
  }
  governors_[type_id] = governor;
}
GovernorsHandler& GovernorsHandler::Get() {
  static GovernorsHandler instance;
  return instance;
}
Governor* GovernorsHandler::GetGovernor(uint64_t type_id) const {
  if (type_id >= governors_.size() || !governors_[type_id]) {
    throw std::logic_error("(GovernorsHandler::GetGovernor) No such governor");
  }
  return governors_[type_id];
}
