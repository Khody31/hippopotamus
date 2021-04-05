#include <stdexcept>

#include "game_object.h"
#include "engine/comp/component.h"

Component* GameObject::GetComponent(int type_id) {
  return components_[type_id];
}

void GameObject::AddComponent(Component* comp) {
  if (components_[comp->GetTypeID()]) {
    throw std::logic_error(
        "(GameObject::AddComponent) Component is already set");
  }
  components_[comp->GetTypeID()] = comp;
  comp->SetParent(this);
}

GameObject::~GameObject() {
  for (auto& comp_ptr : components_) {
    delete comp_ptr.second;
  }
}

void GameObject::OnPulse(int source_id) {
  const auto& subscribers{GovernorsHandler::Get().GetSubscribers(source_id)};
  for (auto sub : subscribers) {
    auto iter{components_.find(sub)};
    if (iter == components_.end()) {
      continue;
    }
    iter->second->parent_governor_->ReceivePulse(source_id, this);
  }
}
