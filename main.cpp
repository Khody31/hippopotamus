#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QApplication>

#include "Engine/Components/pixmap_component.h"
#include "Engine/Core/game_scene.h"
#include "player.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  auto player = new Player;
  GameScene::GetInstance().show();
  return a.exec();
}

