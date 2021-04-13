#include "connector.h"

Connector::Connector() {
  game_coordinator_.Init();

  game_coordinator_.RegisterComponent<TransformationComponent>();
  game_coordinator_.RegisterComponent<PixmapComponent>();

  tr_system_ = game_coordinator_.RegisterSystem<TransformationSystem>();
  render_system_ = game_coordinator_.RegisterSystem<RenderSystem>();

  Signature player_signature;
  player_signature.set(game_coordinator_.GetComponentType<
      TransformationComponent>());
  player_signature.set(game_coordinator_.GetComponentType<PixmapComponent>());

  game_coordinator_.SetSystemSignature<TransformationSystem>(player_signature);
  game_coordinator_.SetSystemSignature<RenderSystem>(player_signature);
  Entity player = game_coordinator_.CreateEntity();
  game_coordinator_.AddComponent(player,
                                 TransformationComponent{{0, 0}, {0, 0}});
  game_coordinator_.AddComponent(player,
                                 PixmapComponent{QPixmap(":/player.png"),
                                                 {0.5, 0.5},
                                                 {675, 325},
                                                 {925, 575}});
}

void Connector::OnTick() {
  // update all (currently two) systems with our game_coordinator_
  tr_system_->Update(&game_coordinator_);
  render_system_->Update(&game_coordinator_);
  // also communicate with future keyboard_listener
}

void Connector::SetScene(QWidget* scene) {
  scene_ = scene;
  render_system_->SetScene(scene);
}

const PixmapComponent& Connector::GetPixmapComponent(Entity entity) {
  return game_coordinator_.GetComponent<PixmapComponent>(entity);
}

const std::set<Entity>& Connector::GetEntitiesToRender() {
  return render_system_->GetEntities();
}
