#include "governor.h"

Governor::Governor(int type_id)
    : type_id_(type_id) {
  GovernorsHandler::Get().SetGovernor(this, type_id);
}

void Governor::StartTracking(Component* comp) {
  components_.insert(comp);
}

void Governor::StopTracking(Component* comp) {
  components_.erase(comp);
}

void Governor::SubscribeFor(int source_id) const {
  GovernorsHandler::Get().Subscribe(type_id_, source_id);
}

const std::set<Component*>& Governor::GetComponents() const {
  return components_;
}
