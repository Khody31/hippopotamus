#include <set>
#include <memory>

#include "connector.h"

Connector::Connector() {
  coordinator_.Init();

  RegisterComponents();
  RegisterSystems();
  CreatePlayer();
  CreateBall();
  CreateWall();
}

void Connector::OnTick() {
  joystick_system_->Update(&coordinator_);
  collision_system_->Update(&coordinator_);
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
  coordinator_.RegisterComponent<TransformationComponent>();
  coordinator_.RegisterComponent<PixmapComponent>();
  coordinator_.RegisterComponent<MotionComponent>();
  coordinator_.RegisterComponent<JoystickComponent>();
  coordinator_.RegisterComponent<CollisionComponent>();
  coordinator_.RegisterComponent<SerializationComponent>();
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
  {
    collision_system_ = coordinator_.RegisterSystem<CollisionSystem>();
    Signature signature;
    signature.set(coordinator_.GetComponentType<TransformationComponent>());
    signature.set(coordinator_.GetComponentType<MotionComponent>());
    signature.set(coordinator_.GetComponentType<CollisionComponent>());
    coordinator_.SetSystemSignature<CollisionSystem>(signature);
  }
  {
    serialization_system = coordinator_.RegisterSystem<SerializationSystem>();
    Signature signature;
    signature.set(coordinator_.GetComponentType<SerializationComponent>());
    coordinator_.SetSystemSignature<SerializationSystem>(signature);
  }
}

void Connector::CreatePlayer() {
  Entity player = coordinator_.CreateEntity();
  coordinator_.AddComponent(player, TransformationComponent{{0, 0}});
  coordinator_.AddComponent(player, MotionComponent{1.0});
  coordinator_.AddComponent(player, JoystickComponent{});
  coordinator_.AddComponent(player, PixmapComponent{QPixmap(":/player.png"),
                                                    {0.2, 0.2}});
  coordinator_.AddComponent(player, CollisionComponent{
      1, 0, {0.2, 0.2}
  });
}

void Connector::OnKeyPress(Qt::Key key) {
  keyboard_interface_.OnPress(key);
}

void Connector::OnKeyRelease(Qt::Key key) {
  keyboard_interface_.OnRelease(key);
}

void Connector::CreateBall() {
  Entity ball = coordinator_.CreateEntity();
  coordinator_.AddComponent(ball, TransformationComponent{{1, 0.2}});
  coordinator_.AddComponent(ball, MotionComponent{1.0});
  coordinator_.AddComponent(ball, PixmapComponent{QPixmap(":/player.png"),
                                                  {0.2, 0.2}});
  coordinator_.AddComponent(ball, CollisionComponent{
      1, 1, {0.2, 0.2}
  });
}

void Connector::CreateWall() {
  Entity wall = coordinator_.CreateEntity();
  coordinator_.AddComponent(wall, TransformationComponent{{0, 0.9}});
  coordinator_.AddComponent(wall, MotionComponent{1.0});
  coordinator_.AddComponent(wall, PixmapComponent{QPixmap(":/player.png"),
                                                  {3.2, 0.2}});
  coordinator_.AddComponent(wall, CollisionComponent{
      0, 1, {3.2, 0.2}
  });
}

void Connector::ChangeRoom(int id) {
  serialization_system->Serialize();

  // TODO(polchernikova) : Destroy old entities

  serialization_system->Deserialize(&coordinator_, id);
}
