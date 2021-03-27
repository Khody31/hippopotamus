#include "game_object.h"
#include "engine/comp/abstract_component.h"

AbstractComponent* GameObject::GetComponent(uint64_t type_id) {
  return components_[type_id];
}
void GameObject::AddComponent(AbstractComponent* comp, uint64_t type_id) {
  if (type_id >= components_.size()) {
    throw std::logic_error("(GameObject::AddComponent) No such component type");
  }
  if (components_[type_id]) {
    throw std::logic_error("(GameObject::AddComponent) Component is already set");
  }
  components_[type_id] = comp;
  comp->SetParent(this);
}
GameObject::~GameObject() {
  for (auto& comp_ptr : components_) {
    delete comp_ptr;
  }
}
