#pragma once

#include <memory>

#include "component_manager.h"
#include "entity_manager.h"
#include "system_manager.h"

class Coordinator {
 public:
  void Init();

  Entity CreateEntity();
  void DestroyEntity(Entity entity);

  template<typename T>
  void RegisterComponent();
  template<typename T>
  void AddComponent(Entity entity, const T& component);
  template<typename T>
  void RemoveComponent(Entity entity);
  template<typename T>
  T& GetComponent(Entity entity);
  template<typename T>
  ComponentType GetComponentType();

  template<typename T>
  std::shared_ptr<T> RegisterSystem();
  template<typename T>
  void SetSystemSignature(Signature signature);
  template<typename T>
  void UpdateSignature(Entity entity, bool has_component);

 private:
  std::unique_ptr<ComponentManager> component_manager_;
  std::unique_ptr<EntityManager> entity_manager_;
  std::unique_ptr<SystemManager> system_manager_;
};

template<typename T>
void Coordinator::RegisterComponent() {
  component_manager_->RegisterComponent<T>();
}

template<typename T>
void Coordinator::AddComponent(Entity entity, const T& component) {
  component_manager_->AddComponent<T>(entity, component);
  UpdateSignature<T>(entity, true);
}

template<typename T>
void Coordinator::RemoveComponent(Entity entity) {
  component_manager_->RemoveComponent<T>(entity);
  UpdateSignature<T>(entity, false);
}

template<typename T>
T& Coordinator::GetComponent(Entity entity) {
  return component_manager_->GetComponent<T>(entity);
}

template<typename T>
ComponentType Coordinator::GetComponentType() {
  return component_manager_->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> Coordinator::RegisterSystem() {
  return system_manager_->RegisterSystem<T>();
}

template<typename T>
void Coordinator::SetSystemSignature(Signature signature) {
  system_manager_->SetSignature<T>(signature);
}

template<typename T>
void Coordinator::UpdateSignature(Entity entity, bool has_component) {
  auto signature = entity_manager_->GetSignature(entity);
  signature.set(component_manager_->GetComponentType<T>(), has_component);
  entity_manager_->SetSignature(entity, signature);
  system_manager_->EntitySignatureChanged(entity, signature);
}
