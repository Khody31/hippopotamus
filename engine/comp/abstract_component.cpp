#include <stdexcept>

#include "abstract_component.h"
#include "engine/gov/governors_handler.h"

GameObject* AbstractComponent::GetParent() const {
  return parent_object_;
}
void AbstractComponent::SetParent(GameObject* new_parent) {
  if (parent_object_) {
    throw std::logic_error("Component already has a parent");
  }
  parent_object_ = new_parent;
}
void AbstractComponent::NotifyGovernor() {
  parent_governor_->ComponentStateChangedEvent(this);
}
AbstractComponent::AbstractComponent(uint64_t type_id) {
  parent_governor_ = GovernorsHandler::Get().GetGovernor(type_id);
  parent_governor_->StartTracking(this);
}
AbstractComponent::~AbstractComponent() {
  parent_governor_->StopTracking(this);
}
