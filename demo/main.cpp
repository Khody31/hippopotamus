#include <QApplication>

#include "engine/system/game_widget.h"
#include "mouse_listener.h"

#include "engine/gov/governor.h"
#include "engine/comp/component.h"

class TempGovernor : public Governor {
 public:
  TempGovernor() : Governor(ComponentIDs::kTransformationID) {}

  void EmitPulse(Component*) {
    std::cerr << "Event received!";
  }
};

class TempComponent : public Component {
 public:
  TempComponent() : Component(ComponentIDs::kTransformationID) {}

  // void SomeEvent() {
  //   NotifyGovernor();
  // }
};

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  TempGovernor governor;
  TempComponent component;
  // component.SomeEvent();

  return QApplication::exec();
}
