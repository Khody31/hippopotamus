#include <QApplication>

#include "engine/system/game_widget.h"
#include "mouse_listener.h"

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

int main(int argc, char** argv) {
  TempGovernor governor;
  TempComponent component;
  component.SomeEvent();

  return QApplication::exec();
}
