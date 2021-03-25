#include "game_object.h"

TransformationComponentInterface* GameObject::GetTransformationComponent() const {
  return transformation_component_;
}

PixmapComponentInterface* GameObject::GetPixmapComponent() const {
  return pixmap_component_;
}

void GameObject::SetTransformationComponent(TransformationComponentInterface* component) {
  transformation_component_ = component;
}

void GameObject::SetPixmapComponent(PixmapComponentInterface* component) {
  pixmap_component_ = component;
}

void GameObject::OnTick() {
  if (transformation_component_ != nullptr) {
    transformation_component_->Update();
  }
  if (pixmap_component_ != nullptr) {
    pixmap_component_->Update();
  }
}

GameObject::GameObject(Entity entity) : entity_(entity) {}
