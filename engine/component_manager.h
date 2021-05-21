#pragma once

#include <bitset>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "component_array.h"
#include "types.h"

class ComponentManager {
 public:
  ComponentManager();

  template<typename T>
  void RegisterComponent();

  template<typename T>
  ComponentType GetComponentType();

  template<typename T>
  void AddComponent(Entity entity, const T& component);

  template<typename T>
  void RemoveComponent(Entity entity);

  template<typename T>
  T& GetComponent(Entity entity);

  void DestroyEntity(Entity entity);

  template<typename T>
  std::shared_ptr<ComponentArray<T>> GetComponentArray();

  template<typename T>
  bool HasComponent(Entity entity);

 private:
  // component type index -> component type
  std::unordered_map<std::type_index, ComponentType> component_types_;

  // component type index -> array of all components of that type
  std::unordered_map<std::type_index,
                     std::shared_ptr<AbstractComponentArray>> component_arrays_;

  ComponentType next_component_type_;
};

template<typename T>
void ComponentManager::RegisterComponent() {
  auto index = std::type_index(typeid(T));
  assert(component_types_.find(index) == component_types_.end() &&
      "Registering component type more than once.");

  component_types_.emplace(index, next_component_type_);
  component_arrays_.emplace(index, std::make_shared<ComponentArray<T>>());
  ++next_component_type_;
}

template<typename T>
ComponentType ComponentManager::GetComponentType() {
  auto index = std::type_index(typeid(T));
  assert(component_types_.find(index) != component_types_.end() &&
      "component not registered before use.");
  return component_types_[index];
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, const T& component) {
  GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity) {
  GetComponentArray<T>()->RemoveData(entity);
}

template<typename T>
T& ComponentManager::GetComponent(Entity entity) {
  return GetComponentArray<T>()->GetData(entity);
}

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray() {
  auto index = std::type_index(typeid(T));
  assert(component_types_.find(index) != component_types_.end()
             && "component not registered before use.");

  return std::static_pointer_cast<ComponentArray<T>>(component_arrays_[index]);
}

template<typename T>
bool ComponentManager::HasComponent(Entity entity) {
  return GetComponentArray<T>()->HasComponent(entity);
}
