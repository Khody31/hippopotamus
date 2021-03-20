#include <QApplication>
#include <QMainWindow>

#include "core/game_scene.h"
#include "core/connector.h"
#include "components/components.h"
#include "systems/transformation_system.h"
#include "View/button_controller.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  auto* controller = new ButtonController();
  auto connector = std::make_shared<Connector>();
  auto scene = std::make_shared<GameScene>(connector);
  return QApplication::exec();
}
