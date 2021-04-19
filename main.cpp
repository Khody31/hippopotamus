#include <QApplication>
#include <QMainWindow>

#include "core/game_scene.h"
#include "view/button_controller.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  auto* button_controller = new ButtonController();
  return QApplication::exec();
}
