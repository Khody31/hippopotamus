#include <QApplication>

#include "engine/system/game_widget.h"
#include "mouse_listener.h"
#include "engine/comp/TEMP.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  GameWidget::Get().setFixedSize(1000, 1000);
  GameWidget::Get().show();
  GameWidget::Get().SetMouseListener(new MouseListener);

  std::cout << ComponentIDs::kNumOfComponents << std::endl;

  TempGovernor governor;
  TempComponent component;
  component.SomeEvent();

  return QApplication::exec();
}
