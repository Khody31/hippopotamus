#include <set>
#include <memory>

#include "connector.h"

Connector::Connector() : scene_(nullptr) {
  coordinator_.Init();

  RegisterComponents();
  RegisterSystems();
  CreatePlayer();

  joystick_system_->SetKeyboardInterface(&keyboard_interface_);
}

void Connector::OnTick() {
  // update all (currently two) systems with our coordinator_
  // tr_system_->Update(&coordinator_);
  joystick_system_->Update(&coordinator_);
  motion_system_->Update(&coordinator_);
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
  coordinator_.RegisterComponent<MotionComponent>();
  coordinator_.RegisterComponent<JoystickComponent>();
}

void Connector::RegisterSystems() {
  tr_system_ = coordinator_.RegisterSystem<TransformationSystem>();
  render_system_ = coordinator_.RegisterSystem<RenderSystem>();
  joystick_system_ = coordinator_.RegisterSystem<JoystickSystem>();
  motion_system_ = coordinator_.RegisterSystem<MotionSystem>();
  {
    Signature signature;
    signature.set(coordinator_.GetComponentType<TransformationComponent>());
    coordinator_.SetSystemSignature<TransformationSystem>(signature);
  }
  {
    Signature signature;
    signature.set(coordinator_.GetComponentType<TransformationComponent>());
    coordinator_.SetSystemSignature<TransformationSystem>(signature);
  }
  {
    Signature signature;
    signature.set(coordinator_.GetComponentType<MotionComponent>());
    signature.set(coordinator_.GetComponentType<JoystickComponent>());
    coordinator_.SetSystemSignature<JoystickSystem>(signature);
  }
  {
    Signature signature;
    signature.set(coordinator_.GetComponentType<MotionComponent>());
    signature.set(coordinator_.GetComponentType<TransformationComponent>());
    coordinator_.SetSystemSignature<MotionSystem>(signature);
  }
}

void Connector::CreatePlayer() {
  Signature player_signature;
  player_signature.set(
      coordinator_.GetComponentType<TransformationComponent>());
  player_signature.set(coordinator_.GetComponentType<PixmapComponent>());

  Entity player = coordinator_.CreateEntity();
  coordinator_.AddComponent(player,
                            TransformationComponent{{0, 0}});
  coordinator_.AddComponent(player,
                            MotionComponent{1.0});
  coordinator_.AddComponent(player,
                            JoystickComponent{});
  coordinator_.AddComponent(player,
                            PixmapComponent{QPixmap(":/player.png"),
                                            {0.5, 0.5}});
}
void Connector::OnKeyPress(Qt::Key key) {
  keyboard_interface_.OnPress(key);
}
void Connector::OnKeyRelease(Qt::Key key) {
  keyboard_interface_.OnRelease(key);
}
