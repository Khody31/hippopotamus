#include <QApplication>
#include "core/game_scene.h"

#include "core/connector.h"
#include "game_components/components.h"
#include "systems/transformation_system.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  auto connector = std::make_shared<Connector>();
  auto scene = std::make_shared<GameScene>(connector);

  return QApplication::exec();
}
