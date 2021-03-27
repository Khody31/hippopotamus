#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QApplication>

#include "Engine/Components/pixmap_component.h"
#include "Engine/Core/game_scene.h"
#include "Engine/Core/game_object.h"
#include "Engine/Entities/player.h"
#include "Engine/Components/transformation_component_player.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  //Создание игрока
  //Это образец того как в будущем нужно будет создавать любых GameObject'ов
  // Мб позже это будет просто функция вида GameObject* CreatePlayer()
  Player player;

  GameScene::GetInstance().SetPlayer(&player);
  GameScene::GetInstance().show();

  return QApplication::exec();
}

