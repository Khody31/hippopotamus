#include <QApplication>
#include <QMainWindow>

#include "core/game_scene.h"
#include "view/controller.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  auto* button_controller = new Controller();
  return QApplication::exec();
}
