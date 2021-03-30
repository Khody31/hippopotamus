#ifndef GOVERNOR_H_
#define GOVERNOR_H_

#include <set>

#include "engine/core/game_object.h"
#include "governors_handler.h"

class Component;

class Governor {
 public:
  explicit Governor(int type_id);
  virtual ~Governor() = default;

  virtual void OnTick() {}

  void StartTracking(Component*);
  void StopTracking(Component*);

  void SubscribeFor(int source_id) const;
  virtual void ReceivePulse(int source_id, GameObject*) {};

 protected:
  std::set<Component*> components_;

  int type_id_;
};

#endif  // GOVERNOR_H_
