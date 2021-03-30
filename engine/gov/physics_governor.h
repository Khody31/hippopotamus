#ifndef PHYSICS_GOVERNOR_H_
#define PHYSICS_GOVERNOR_H_

#include "governor.h"

class PhysicsGovernor : public Governor {
 public:
  explicit PhysicsGovernor(int type_id);

  void OnTick() override;
};

#endif  // PHYSICS_GOVERNOR_H_
