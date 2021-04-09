#include <QApplication>

#include "engine/coordinator.h"
#include "game_components/components.h"
#include "systems/transformation_system.h"

int main(int argc, char** argv) {
  Coordinator game_coordinator;

  game_coordinator.Init();

  game_coordinator.RegisterComponent<TransformationComponent>();

  auto tr_system = game_coordinator.RegisterSystem<TransformationSystem>();

  Signature player_signature;
  player_signature.set(game_coordinator.GetComponentType<TransformationComponent>());

  game_coordinator.SetSystemSignature<TransformationSystem>(player_signature);
  Entity player = game_coordinator.CreateEntity();
  game_coordinator.AddComponent(player,
                                TransformationComponent{}); // add arguments

}
