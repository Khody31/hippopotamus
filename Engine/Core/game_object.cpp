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
  transformation_component_->Update();
  // pixmap_component_->Update();
  // не понятно пока, что будет делать PixmapComponent::Update. Но строчка
  // служит образоцом. Чтоб понять, что в OnTick у любого GameObject мы просто
  // вызываем Update всех его компонент, которые при необходимости
  // могут посмотреть родительское поле Entity. Но суть даже не в этом,
  // а в том, что эти компоненты вызывают именно виртуальную функцию Update
  // нужного нам класса (Например BulletTransformationComponent::Update)
}

GameObject::GameObject(Entity entity) : entity_(entity) {}


