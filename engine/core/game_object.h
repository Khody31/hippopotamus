#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <map>

#include "engine/comp/system_comp_ids.h"

class Component;

class GameObject {
 public:
  Component* GetComponent(int type_id);
  void AddComponent(Component*, int type_id);

  ~GameObject();

  void OnPulse(int source_id);

 private:
  std::map<int, Component*> components_{};
};

#endif  // GAME_OBJECT_H_
