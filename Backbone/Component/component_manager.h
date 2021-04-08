#pragma ones

#include <bitset>
#include <memory>

#include "Backbone/constants.h"
#include "component_array.h"

using Entity = uint8_t;
using ComponentType = uint8_t;
using Signature = std::bitset<constants::MAX_COMPONENTS>;

class ComponentManager
{
 public:
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

  void EntityDestroyed(Entity entity);

  template<typename T>
  std::shared_ptr<ComponentArray<T>> GetComponentArray();

 private:
  // component type name -> component type
  std::unordered_map<const char*, ComponentType> mComponentTypes{};

  // component type name -> array of all components of that type
  std::unordered_map<const char*, std::shared_ptr<ComponentArrayInterface>>
  mComponentArrays{};

  ComponentType mNextComponentType{};
};

template<typename T>
void ComponentManager::RegisterComponent() {
  const char* typeName = typeid(T).name();
  assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

  mComponentTypes.insert({typeName, mNextComponentType});
  mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
  ++mNextComponentType;
}

template<typename T>
ComponentType ComponentManager::GetComponentType() {
  const char* typeName = typeid(T).name();
  assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");
  return mComponentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, T component)  {
  GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity) {
  GetComponentArray<T>()->RemoveData(entity);
}

template<typename T>
T &ComponentManager::GetComponent(Entity entity) {
  return GetComponentArray<T>()->GetData(entity);
}

void ComponentManager::EntityDestroyed(Entity entity) {
  for (auto const& pair : mComponentArrays)
  {
    auto const& component = pair.second;

    component->EntityDestroyed(entity);
  }
}

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray() {
  const char* typeName = typeid(T).name();

  assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

  return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
}
