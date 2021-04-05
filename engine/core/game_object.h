#pragma  once

#include <map>

#include "engine/comp/system_comp_ids.h"

class Component;

class GameObject {
 public:
  Component* GetComponent(int type_id);
  void AddComponent(Component*);

  ~GameObject();

  void OnPulse(int source_id);

 private:
  std::map<int, Component*> components_{};
};
