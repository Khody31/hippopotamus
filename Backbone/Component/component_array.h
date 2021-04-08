#pragma once

#include <unordered_map>
#include <cassert>

#include "component_array_interface.h"
#include "Backbone/constants.h"


template<typename T>
class ComponentArray : public ComponentArrayInterface
{
 public:
  void InsertData(Entity entity, T component);
  void RemoveData(Entity entity);

  T& GetData(Entity entity);

  void EntityDestroyed(Entity entity) override;

 private:
  // array of all existing components of specific type T
  std::array<T, constants::MAX_ENTITIES> mComponentArray;

  // entity ID -> array index
  std::unordered_map<Entity, size_t> mEntityToIndexMap;

  // array index -> entity ID
  std::unordered_map<size_t, Entity> mIndexToEntityMap;

  // number of existing entities
  size_t mSize;
};

template<typename T>
void ComponentArray<T>::InsertData(Entity entity, T component) {
  assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

  size_t newIndex = mSize;
  mEntityToIndexMap[entity] = newIndex;
  mIndexToEntityMap[newIndex] = entity;
  mComponentArray[newIndex] = component;
  ++mSize;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity entity) {
  assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

  size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
  size_t indexOfLastElement = mSize - 1;
  mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

  Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
  mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
  mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

  mEntityToIndexMap.erase(entity);
  mIndexToEntityMap.erase(indexOfLastElement);
  --mSize;
}

template<typename T>
T &ComponentArray<T>::GetData(Entity entity) {
  assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

  return mComponentArray[mEntityToIndexMap[entity]];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(Entity entity) {
  if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
  {
    RemoveData(entity);
  }
}
