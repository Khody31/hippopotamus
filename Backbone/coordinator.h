#pragma once

#include "Component/component_manager.h"
#include "Entity/entity_manager.h"
#include "System/system_manager.h"


class Coordinator
{
 public:
  void Init();

  Entity CreateEntity();
  void DestroyEntity(Entity entity);

  template<typename T>
  void RegisterComponent();
  template<typename T>
  void AddComponent(Entity entity, T component);
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

 private:
  std::unique_ptr<ComponentManager> mComponentManager;
  std::unique_ptr<EntityManager> mEntityManager;
  std::unique_ptr<SystemManager> mSystemManager;
};