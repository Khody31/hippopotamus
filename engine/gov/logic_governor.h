#ifndef LOGIC_GOVERNOR_H_
#define LOGIC_GOVERNOR_H_

#include "governor.h"

class LogicGovernor : public Governor {
 public:
  LogicGovernor();
  void OnTick() override;

 private:
};

#endif  // LOGIC_GOVERNOR_H_
