#pragma  once

#include "component.h"

class LogicComponent : public Component {
 public:
  LogicComponent();
  virtual void OnTick() = 0;
};

