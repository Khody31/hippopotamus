#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QApplication>

#include "Engine/Components/pixmap_component.h"
#include "Engine/Core/game_scene.h"
#include "Engine/Core/game_object.h"
#include "Engine/Components/transformation_component_player.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  //Создание игрока
  //Это образец того как в будущем нужно будет создавать любых GameObject'ов
  // Мб позже это будет просто функция вида GameObject* CreatePlayer()
  GameObject player(Entity::kPlayer);
  player.SetPixmapComponent(new PixmapComponent(
      &player, {0.5, 0.5}, SceneLayerID::kBackground,
      ":/textures/some_basic_player.png"));
  player.SetTransformationComponent(new TransformationComponentPlayer);

  GameScene::GetInstance().show();
  GameTimer::GetInstance().scene_ = &GameScene::GetInstance();

  return a.exec();
}

