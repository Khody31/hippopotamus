#pragma  once

#include "governor.h"

class LogicGovernor : public Governor {
 public:
  LogicGovernor();
  void OnTick() override;

 private:
};
