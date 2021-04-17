#include <set>
#include <memory>
#include "QWidget"

#include "connector.h"
#include "game_constants.h"

Connector::Connector()
    : game_coordinator_(), tr_system_(), render_system_(), scene_(nullptr) {
  game_coordinator_.Init();

  RegisterComponents();
  RegisterSystems();
  CreatePlayer();
}

void Connector::OnTick() {
  // update all (currently two) systems with our game_coordinator_
  tr_system_->Update(&game_coordinator_);
  render_system_->Update(&game_coordinator_);
  bullet_system->Update(&game_coordinator_);
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
  game_coordinator_.RegisterComponent<BulletIdentifierComponent>();
}

void Connector::RegisterSystems() {
  tr_system_ = game_coordinator_.RegisterSystem<TransformationSystem>();
  render_system_ = game_coordinator_.RegisterSystem<RenderSystem>();
  bullet_system = game_coordinator_.RegisterSystem<BulletSystem>();
}

void Connector::CreatePlayer() {
  Signature player_signature;
  player_signature.set(game_coordinator_.GetComponentType<
      TransformationComponent>());
  player_signature.set(game_coordinator_.GetComponentType<PixmapComponent>());

  game_coordinator_.SetSystemSignature<TransformationSystem>(player_signature);
  game_coordinator_.SetSystemSignature<RenderSystem>(player_signature);

  //
  Signature bullet_system_signature;
  bullet_system_signature.set(
      game_coordinator_.GetComponentType<BulletIdentifierComponent>());
 game_coordinator_.SetSystemSignature<BulletSystem>(bullet_system_signature);
  //

  Entity player = game_coordinator_.CreateEntity();
  bullet_system->SetPlayer(player);
  game_coordinator_.AddComponent(player,
                                 TransformationComponent{{0, 0}, {0, 0}});
  game_coordinator_.AddComponent(player,
                                 PixmapComponent{QPixmap(":/player.png"),
                                                 {0.5, 0.5},
                                                 {0, 0},
                                                 {0, 0}});
}

void Connector::MouseClick(const QVector2D& pos_in_game) {
  bullet_system->CreateBullet(pos_in_game,
                              &game_coordinator_);
}
