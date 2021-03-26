#include <QApplication>

#include "engine/core/game_scene.h"
#include "engine/entities/player.h"

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

