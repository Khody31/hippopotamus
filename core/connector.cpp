#include <memory>
#include <unordered_set>

#include "helpers.h"
#include "connector.h"
#include "game_scene.h"

Connector::Connector() {
  RegisterComponents();
  RegisterSystems();

  spawner_ = std::make_shared<Spawner>(&coordinator_);

  Entity player = spawner_->CreatePlayer({0, 0});
  SetPlayer(player);

  spawner_->CreateBall({1, 0});
  spawner_->CreateWall({0, 0.9});
}

void Connector::OnTick() {
  joystick_system_->Update(&coordinator_);
  collision_system_->Update(&coordinator_);
  movement_system_->Update(&coordinator_);
  render_system_->Update(scene_);
}

void Connector::SetScene(GameScene* scene) {
  scene_ = scene;
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

void Connector::OnKeyPress(Qt::Key key) {
  keyboard_interface_.OnPress(key);
}

void Connector::OnKeyRelease(Qt::Key key) {
  keyboard_interface_.OnRelease(key);
}

void Connector::OnMousePress(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    spawner_->CreateBulletFor(
        player_,
        helpers::WidgetToGameCoord(event->pos(), scene_->size()));
  }
}

const PixmapComponent& Connector::GetPixmapComponent(Entity entity) {
  return coordinator_.GetComponent<PixmapComponent>(entity);
}

const TransformationComponent& Connector::GetTransformComponent(Entity entity) {
  return coordinator_.GetComponent<TransformationComponent>(entity);
}

const std::unordered_set<Entity>& Connector::GetEntitiesToRender() const {
  return render_system_->GetEntities();
}

void Connector::SetPlayer(Entity player) {
  player_ = player;
}

void Connector::ChangeRoom(int id) {
  serialization_system->Serialize(&coordinator_);

  // TODO(polchernikova) : Destroy old entities

  serialization_system->Deserialize(&coordinator_, id);
}
