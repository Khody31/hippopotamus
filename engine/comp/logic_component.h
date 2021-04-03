#ifndef LOGIC_COMPONENT_H_
#define LOGIC_COMPONENT_H_

#include "component.h"

class LogicComponent : public Component {
 public:
  LogicComponent();
  virtual void OnTick() = 0;
};

#endif  // LOGIC_COMPONENT_H_
