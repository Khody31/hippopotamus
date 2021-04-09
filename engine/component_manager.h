#pragma once

#include <bitset>
#include <memory>
#include <typeindex>

#include "component_array.h"
#include "types.h"
#include "game_components/components.h"

class ComponentManager {
 public:
  // type -> type name
  static std::unordered_map<std::type_index, const char*> type_names_;

  ComponentManager() : next_component_type_(0) {};

  template<typename T>
  void RegisterComponent();

  template<typename T>
  ComponentType GetComponentType();

  template<typename T>
  void AddComponent(Entity entity, T component);

  template<typename T>
  void RemoveComponent(Entity entity);

  template<typename T>
  T& GetComponent(Entity entity);

  void EntityDestroyed(Entity entity) {
    for (auto const& pair : component_arrays_) {
      auto const& component = pair.second;

      component->EntityDestroyed(entity);
    }
  }

  template<typename T>
  std::shared_ptr<ComponentArray<T>> GetComponentArray();

 private:

  // component type name -> component type
  std::unordered_map<const char*, ComponentType> component_types_{};

  // component type name -> array of all game_components of that type
  std::unordered_map<const char*, std::shared_ptr<AbstractComponentArray>>
      component_arrays_{};

  ComponentType next_component_type_;
};

template<typename T>
void ComponentManager::RegisterComponent() {
  const char* type_name = type_names_[typeid(T)];
  assert(component_types_.find(type_name) == component_types_.end() &&
      "Registering component type more than once.");

  component_types_.insert({type_name, next_component_type_});
  component_arrays_.insert({type_name, std::make_shared<ComponentArray<T>>()});
  ++next_component_type_;
}

template<typename T>
ComponentType ComponentManager::GetComponentType() {
  const char* type_name = type_names_[typeid(T)];
  assert(component_types_.find(type_name) != component_types_.end() &&
      "component not registered before use.");
  return component_types_[type_name];
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, T component) {
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
  const char* type_name = type_names_[typeid(T)];

  assert(component_types_.find(type_name) != component_types_.end()
             && "component not registered before use.");

  return std::static_pointer_cast<ComponentArray<T>>(
      component_arrays_[type_name]);
}

