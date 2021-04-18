#include <set>
#include <memory>

#include "connector.h"

Connector::Connector() {
  coordinator_.Init();

  RegisterComponents();
  RegisterSystems();
  CreatePlayer();
}

void Connector::OnTick() {
  // update all (currently three) systems with our game_coordinator_
  collision_system_->Update(&game_coordinator_);
  render_system_->Update(&game_coordinator_);
  // also communicate with future keyboard_listener
  joystick_system_->Update(&coordinator_);
  movement_system_->Update(&coordinator_);
  render_system_->Update(&coordinator_);
}

void Connector::SetScene(QWidget* scene) {
  render_system_->SetScene(scene);
}

const PixmapComponent& Connector::GetPixmapComponent(Entity entity) {
  return coordinator_.GetComponent<PixmapComponent>(entity);
}

const std::set<Entity>& Connector::GetEntitiesToRender() {
  return render_system_->GetEntities();
}

void Connector::RegisterComponents() {
<<<<<<< HEAD
  game_coordinator_.RegisterComponent<TransformationComponent>();
  game_coordinator_.RegisterComponent<PixmapComponent>();
  game_coordinator_.RegisterComponent<CollisionComponent>();
}

void Connector::RegisterSystems() {
  tr_system_ = game_coordinator_.RegisterSystem<TransformationSystem>();
  render_system_ = game_coordinator_.RegisterSystem<RenderSystem>();
  collision_system_ = game_coordinator_.RegisterSystem<CollisionSystem>();
=======
  coordinator_.RegisterComponent<TransformationComponent>();
  coordinator_.RegisterComponent<PixmapComponent>();
  coordinator_.RegisterComponent<MotionComponent>();
  coordinator_.RegisterComponent<JoystickComponent>();
}

void Connector::RegisterSystems() {
  {
    render_system_ = coordinator_.RegisterSystem<RenderSystem>();
    Signature signature;
    signature.set(coordinator_.GetComponentType<TransformationComponent>());
    signature.set(coordinator_.GetComponentType<PixmapComponent>());
    coordinator_.SetSystemSignature<RenderSystem>(signature);
  }
  {
    joystick_system_ = coordinator_.RegisterSystem<JoystickSystem>();
    Signature signature;
    signature.set(coordinator_.GetComponentType<MotionComponent>());
    signature.set(coordinator_.GetComponentType<JoystickComponent>());
    coordinator_.SetSystemSignature<JoystickSystem>(signature);
    joystick_system_->SetKeyboardInterface(&keyboard_interface_);
  }
  {
    movement_system_ = coordinator_.RegisterSystem<MovementSystem>();
    Signature signature;
    signature.set(coordinator_.GetComponentType<MotionComponent>());
    signature.set(coordinator_.GetComponentType<TransformationComponent>());
    coordinator_.SetSystemSignature<MovementSystem>(signature);
  }
>>>>>>> master
}

void Connector::CreatePlayer() {
  Signature player_signature;
  player_signature.set(
<<<<<<< HEAD
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
=======
      coordinator_.GetComponentType<TransformationComponent>());
  player_signature.set(coordinator_.GetComponentType<PixmapComponent>());

  Entity player = coordinator_.CreateEntity();
  coordinator_.AddComponent(player, TransformationComponent{{0, 0}});
  coordinator_.AddComponent(player, MotionComponent{1.0});
  coordinator_.AddComponent(player, JoystickComponent{});
  coordinator_.AddComponent(player, PixmapComponent{QPixmap(":/player.png"),
                                                    {0.5, 0.5}});
}

void Connector::OnKeyPress(Qt::Key key) {
  keyboard_interface_.OnPress(key);
}

void Connector::OnKeyRelease(Qt::Key key) {
  keyboard_interface_.OnRelease(key);
>>>>>>> master
}
