#include <QApplication>

#include "view/controller.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  QApplication::setWindowIcon(QIcon(":/menu/favicon.ico"));

  auto controller = std::make_unique<Controller>();

  return QApplication::exec();
}
