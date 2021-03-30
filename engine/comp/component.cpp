#include <stdexcept>

#include "component.h"

GameObject* Component::GetParent() const {
  return parent_object_;
}
void Component::SetParent(GameObject* new_parent) {
  if (parent_object_) {
    throw std::logic_error("Component already has a parent");
  }
  parent_object_ = new_parent;
}

Component::Component(uint64_t type_id, GameObject* parent)
    : type_id_(type_id), parent_object_(parent) {
  parent_governor_ = GovernorsHandler::Get().GetGovernor(type_id);
  parent_governor_->StartTracking(this);
}

Component::~Component() {
  parent_governor_->StopTracking(this);
}

void Component::EmitPulse() {
  parent_object_->OnPulse(type_id_);
}
