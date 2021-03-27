#ifndef TEMP_H_
#define TEMP_H_

#include "engine/gov/governor.h"
#include "engine/comp/abstract_component.h"

class TempGovernor : public Governor {
 public:
  TempGovernor() : Governor(ComponentIDs::kTransformationID) {}

  void ComponentStateChangedEvent(AbstractComponent*) override {
    std::cerr << "Event received!";
  }
};

class TempComponent : public AbstractComponent {
 public:
  TempComponent() : AbstractComponent(ComponentIDs::kTransformationID) {}

  void SomeEvent() {
    NotifyGovernor();
  }
};

#endif  // TEMP_H_
