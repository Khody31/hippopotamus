#include <memory>
#include <unordered_set>

#include "helpers.h"
#include "connector.h"
#include "game_scene.h"

#include <QDebug>

Connector::Connector() {
  RegisterComponents();
  RegisterSystems();

  spawner_ = std::make_shared<Spawner>(&coordinator_);
  StartGame();
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
  coordinator_.RegisterComponent<DoorComponent>();
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
    collision_system_->SetKeyboardInterface(&keyboard_interface_);
    collision_system_->SetConnector(this);
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

const std::set<Entity>& Connector::GetEntitiesToRender() const {
  return render_system_->GetEntities();
}

void Connector::SetPlayer(Entity player) {
  player_ = player;
}

void Connector::ChangeRoom(const DoorComponent& component) {
  int id = component.next_room_id;
  QVector2D pos = component.move_player_to;

  scene_->StopTimer();
  serialization_system->Serialize(&coordinator_, current_room_id_);
  serialization_system->Deserialize(&coordinator_, id, spawner_.get());
  current_room_id_ = id;

  coordinator_.GetComponent<TransformationComponent>(player_).pos = pos;
  scene_->StartTimer();
}

void Connector::StartGame() {
  Entity player = spawner_->CreatePlayer({0, 0});
  SetPlayer(player);

  spawner_->CreateWalls();
  spawner_->CreateDoor({0, 0.84});

  serialization_system->Deserialize(&coordinator_, 0, spawner_.get());
  current_room_id_ = 0;
}

