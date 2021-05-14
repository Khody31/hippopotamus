#pragma once

#include <cassert>
#include <unordered_map>

#include "abstract_component_array.h"
#include "constants.h"

template<typename T>
class ComponentArray : public AbstractComponentArray {
 public:
  ComponentArray();

  void InsertData(Entity entity, const T& component);
  void RemoveData(Entity entity);
  T& GetData(Entity entity);

  void DestroyEntity(Entity entity) override;

  bool HasComponent(Entity entity);

 private:
  // array of all existing components of specific type T
  std::array<T, constants::kMaxEntities> component_array_;

  // entity ID -> array index
  std::unordered_map<Entity, uint32_t> entity_to_index_;

  // array index -> entity ID
  std::unordered_map<uint32_t, Entity> index_to_entity_;

  // number of existing entities
  uint32_t size_;
};

template<typename T>
ComponentArray<T>::ComponentArray() : size_(0) {}

template<typename T>
void ComponentArray<T>::InsertData(Entity entity, const T& component) {
  assert(entity_to_index_.find(entity) == entity_to_index_.end() &&
      "component added to same entity more than once.");

  uint32_t new_index = size_;
  entity_to_index_[entity] = new_index;
  index_to_entity_[new_index] = entity;
  component_array_[new_index] = component;
  ++size_;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity entity) {
  assert(entity_to_index_.find(entity) != entity_to_index_.end() &&
      "Removing non-existent component.");

  uint32_t index_of_removed_entity = entity_to_index_[entity];
  uint32_t index_of_last_element = size_ - 1;
  component_array_[index_of_removed_entity] =
      component_array_[index_of_last_element];

  Entity entity_of_last_element = index_to_entity_[index_of_last_element];
  entity_to_index_[entity_of_last_element] = index_of_removed_entity;
  index_to_entity_[index_of_removed_entity] = entity_of_last_element;

  entity_to_index_.erase(entity);
  index_to_entity_.erase(index_of_last_element);
  --size_;
}

template<typename T>
T& ComponentArray<T>::GetData(Entity entity) {
  assert(entity_to_index_.find(entity) != entity_to_index_.end() &&
      "Retrieving non-existent component.");

  return component_array_[entity_to_index_[entity]];
}

template<typename T>
void ComponentArray<T>::DestroyEntity(Entity entity) {
  if (entity_to_index_.find(entity) != entity_to_index_.end()) {
    RemoveData(entity);
  }
}

template<typename T>
bool ComponentArray<T>::HasComponent(Entity entity) {
  return entity_to_index_.find(entity) != entity_to_index_.end();
}
