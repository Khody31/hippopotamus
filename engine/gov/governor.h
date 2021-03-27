#ifndef GOVERNOR_H_
#define GOVERNOR_H_

#include <set>

#include "governors_handler.h"

class AbstractComponent;

class Governor {
 public:
  explicit Governor(uint64_t type_id);

  virtual void OnTick() {}
  virtual void ComponentStateChangedEvent(AbstractComponent*) {}

  void StartTracking(AbstractComponent*);
  void StopTracking(AbstractComponent*);

 private:
  std::set<AbstractComponent*> components_;
};

#endif  // GOVERNOR_H_
