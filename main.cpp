#include <QApplication>

#include "engine/coordinator.h"
#include "game_components/components.h"
#include "systems/transformation_system.h"
#include "core/game_timer.h"

Coordinator game_coordinator;

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  game_coordinator.Init();

  game_coordinator.RegisterComponent<PhysicsComponent>();
  game_coordinator.RegisterComponent<PixmapComponent>();
  game_coordinator.RegisterComponent<TransformationComponent>();

  auto tr_system = game_coordinator.RegisterSystem<TransformationSystem>();

  Signature player_signature;
  player_signature.set(game_coordinator.GetComponentType<PhysicsComponent>());
  player_signature.set(game_coordinator.GetComponentType<PixmapComponent>());
  player_signature.set(game_coordinator.GetComponentType<TransformationComponent>());

  game_coordinator.SetSystemSignature<TransformationSystem>(player_signature);
  Entity player = game_coordinator.CreateEntity();
  game_coordinator.AddComponent(player, PhysicsComponent{}); // add arguments
  game_coordinator.AddComponent(player, PixmapComponent{
    .pixmap_ = QPixmap(":/player.png"),
    .size_ = {0.5, 0.5}});
  game_coordinator.AddComponent(player, TransformationComponent{}); // add arguments

  GameTimer* timer = new GameTimer;

  return QApplication::exec();
}