#include "connector.h"

Connector::Connector() {
  game_coordinator_.Init();

  game_coordinator_.RegisterComponent<TransformationComponent>();

  tr_system_ = game_coordinator_.RegisterSystem<TransformationSystem>();

  Signature player_signature;
  player_signature.set(game_coordinator_.GetComponentType<TransformationComponent>());

  game_coordinator_.SetSystemSignature<TransformationSystem>(player_signature);
  Entity player = game_coordinator_.CreateEntity();
  game_coordinator_.AddComponent(player,
                                TransformationComponent{}); // add arguments
  tr_system_->Update(&game_coordinator_);
}

void Connector::OnTick() {
  // update all (currently one) systems with our game_coordinator_
  tr_system_->Update(&game_coordinator_);
}
