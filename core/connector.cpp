#include <set>
#include <memory>

#include "connector.h"

Connector::Connector() : scene_(nullptr) {
  game_coordinator_.Init();

  RegisterComponents();
  RegisterSystems();
  CreatePlayer();
}

void Connector::OnTick() {
  // update all (currently three) systems with our game_coordinator_
  tr_system_->Update(&game_coordinator_);
  collision_system_->Update(&game_coordinator_);
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

void Connector::RegisterComponents() {
  game_coordinator_.RegisterComponent<TransformationComponent>();
  game_coordinator_.RegisterComponent<PixmapComponent>();
  game_coordinator_.RegisterComponent<CollisionComponent>();
}

void Connector::RegisterSystems() {
  tr_system_ = game_coordinator_.RegisterSystem<TransformationSystem>();
  render_system_ = game_coordinator_.RegisterSystem<RenderSystem>();
  collision_system_ = game_coordinator_.RegisterSystem<CollisionSystem>();
}

void Connector::CreatePlayer() {
  Signature player_signature;
  player_signature.set(
      game_coordinator_.GetComponentType<TransformationComponent>());
  player_signature.set(
      game_coordinator_.GetComponentType<PixmapComponent>());
  player_signature.set(
      game_coordinator_.GetComponentType<CollisionComponent>());

  game_coordinator_.SetSystemSignature<TransformationSystem>(player_signature);
  game_coordinator_.SetSystemSignature<RenderSystem>(player_signature);
  game_coordinator_.SetSystemSignature<CollisionSystem>(player_signature);
  Entity player = game_coordinator_.CreateEntity();
  game_coordinator_.AddComponent(player,
                                 TransformationComponent{{0, 0}, {0.0, 0}});
  game_coordinator_.AddComponent(player,
                                 PixmapComponent{QPixmap(":/player.png"),
                                                 {0.5, 0.5},
                                                 {675, 325},
                                                 {925, 575}});
  game_coordinator_.AddComponent(player,
                                 CollisionComponent{
                                     1,
                                     0.5,
                                     {0.-1, 0.-1},
                                     {0.1, 0.1},
                                     {0, 0}
  });
}
