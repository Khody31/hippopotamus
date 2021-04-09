#include <QApplication>

#include "core/connector.h"
#include "game_components/components.h"
#include "systems/transformation_system.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  auto connector = std::make_shared<Connector>();

  return QApplication::exec();
}
