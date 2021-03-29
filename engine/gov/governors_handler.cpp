#include "governors_handler.h"
#include "governor.h"

void GovernorsHandler::SetGovernor(Governor* governor, int type_id) {
  if (governors_.contains(type_id)) {
    throw std::logic_error(
        "(GovernorsHandler::SetGovernor) Another governor is already set");
  }
  governors_.insert({type_id, governor});
}
GovernorsHandler& GovernorsHandler::Get() {
  static GovernorsHandler instance;
  return instance;
}
Governor* GovernorsHandler::GetGovernor(int type_id) const {
  return governors_.at(type_id);
}
void GovernorsHandler::Subscribe(int subscriber_id, int source_id) {
  std::vector<int>& list = subscribers_lists_[source_id];
  if (find(list.begin(), list.end(), subscriber_id) != list.end()) {
    throw std::logic_error("(GovernorsHandler::Subscribe) Already subscribed");
  }
  list.push_back(subscriber_id);
}
const std::vector<int>&
GovernorsHandler::GetSubscribers(int source_id) {
  return subscribers_lists_[source_id];
}
void GovernorsHandler::OnTick() {
  for (auto& gov : governors_) {
    gov.second->OnTick();
  }
}
