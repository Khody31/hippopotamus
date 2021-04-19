#include <QApplication>
#include <QMainWindow>

#include "core/game_scene.h"
#include "core/connector.h"
#include "components/components.h"
#include "systems/transformation_system.h"
#include "view/button_controller.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  auto* button_controller = new ButtonController();
  return QApplication::exec();
}
