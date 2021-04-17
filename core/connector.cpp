#include <set>
#include <memory>

#include "connector.h"

Connector::Connector() : scene_(nullptr) {
  coordinator_.Init();

  RegisterComponents();
  RegicterSystems();
  CreatePlayer();
}

void Connector::OnTick() {
  // update all (currently two) systems with our coordinator_
  tr_system_->Update(&coordinator_);
  render_system_->Update(&coordinator_);
  // also communicate with future keyboard_listener
}

void Connector::SetScene(QWidget* scene) {
  scene_ = scene;
  render_system_->SetScene(scene);
}

const PixmapComponent& Connector::GetPixmapComponent(Entity entity) {
  return coordinator_.GetComponent<PixmapComponent>(entity);
}

const std::set<Entity>& Connector::GetEntitiesToRender() {
  return render_system_->GetEntities();
}

void Connector::RegisterComponents() {
  coordinator_.RegisterComponent<TransformationComponent>();
  coordinator_.RegisterComponent<PixmapComponent>();
}

void Connector::RegicterSystems() {
  tr_system_ = coordinator_.RegisterSystem<TransformationSystem>();
  render_system_ = coordinator_.RegisterSystem<RenderSystem>();
}

void Connector::CreatePlayer() {
  Signature player_signature;
  player_signature.set(coordinator_.GetComponentType<
      TransformationComponent>());
  player_signature.set(coordinator_.GetComponentType<PixmapComponent>());

  coordinator_.SetSystemSignature<TransformationSystem>(player_signature);
  coordinator_.SetSystemSignature<RenderSystem>(player_signature);
  Entity player = coordinator_.CreateEntity();
  coordinator_.AddComponent(player,
                            TransformationComponent{{0, 0}, {0, 0}});
  coordinator_.AddComponent(player,
                            PixmapComponent{QPixmap(":/player.png"),
                                            {0.5, 0.5},
                                            {675, 325},
                                            {925, 575}});
}
