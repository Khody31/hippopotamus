#include <QApplication>

#include "core/game_scene.h"
#include "core/connector.h"
#include "components/components.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Q_INIT_RESOURCE(res);

  auto connector = std::make_shared<Connector>();
  auto scene = std::make_shared<GameScene>(connector);

  return QApplication::exec();
}
