#include <QApplication>

#include "view/controller.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  auto controller = std::make_unique<Controller>();

  return QApplication::exec();
}