#pragma  once

#include "governor.h"

class PhysicsGovernor : public Governor {
 public:
  explicit PhysicsGovernor(int type_id);

  void OnTick() override;
};
