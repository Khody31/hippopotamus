#include <iostream>

#include "Backbone/coordinator.h"
#include "Components/components.h"
#include "Systems/transformation_system.h"
#include "Core/game_timer.h"

Coordinator game_coordinator;

int main() {
  game_coordinator.Init();

  game_coordinator.RegisterComponent<PhysicsComponent>();
  game_coordinator.RegisterComponent<PixmapComponent>();
  game_coordinator.RegisterComponent<TransformationComponent>();

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


}