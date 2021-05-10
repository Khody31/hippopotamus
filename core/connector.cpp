#include <memory>
#include <unordered_set>

#include "helpers.h"
#include "connector.h"
#include "scene.h"

Connector::Connector(QWidget* parent, AbstractController* controller)
    : scene_(std::make_shared<Scene>(this, controller, parent)),
      coordinator_(std::make_shared<Coordinator>()),
      keyboard_(std::make_shared<KeyboardInterface>()),
      spawner_(std::make_shared<Spawner>(coordinator_.get())) {
  RegisterComponents();
  RegisterSystems();
  LoadGame();
}

void Connector::OnTick() {
  joystick_system_->Update();
  collision_system_->Update();
  movement_system_->Update();
  render_system_->Update();
  death_system_->Update();
}

void Connector::RegisterComponents() {
  coordinator_->RegisterComponent<TransformationComponent>();
  coordinator_->RegisterComponent<PixmapComponent>();
  coordinator_->RegisterComponent<MotionComponent>();
  coordinator_->RegisterComponent<JoystickComponent>();
  coordinator_->RegisterComponent<CollisionComponent>();
  coordinator_->RegisterComponent<SerializationComponent>();
  coordinator_->RegisterComponent<DoorComponent>();
  coordinator_->RegisterComponent<HealthComponent>();
  coordinator_->RegisterComponent<DamageComponent>();
  coordinator_->RegisterComponent<IsBulletComponent>();
  coordinator_->RegisterComponent<IntelligenceComponent>();
}

void Connector::RegisterSystems() {
  render_system_ = coordinator_->RegisterSystem<RenderSystem>(scene_.get());
  coordinator_->SetSystemSignature<RenderSystem>(
      {coordinator_->GetComponentType<TransformationComponent>(),
       coordinator_->GetComponentType<PixmapComponent>()});

  joystick_system_ =
      coordinator_->RegisterSystem<JoystickSystem>(coordinator_.get(),
                                                   keyboard_.get());
  coordinator_->SetSystemSignature<JoystickSystem>
      ({coordinator_->GetComponentType<MotionComponent>(),
        coordinator_->GetComponentType<JoystickComponent>()});

  movement_system_ =
      coordinator_->RegisterSystem<MovementSystem>(coordinator_.get());
  coordinator_->SetSystemSignature<MovementSystem>(
      {coordinator_->GetComponentType<MotionComponent>(),
       coordinator_->GetComponentType<TransformationComponent>()
      });
  collision_system_ =
      coordinator_->RegisterSystem<CollisionSystem>(this, coordinator_.get(),
                                                    keyboard_.get());
  coordinator_->SetSystemSignature<CollisionSystem>(
      {coordinator_->GetComponentType<TransformationComponent>(),
       coordinator_->GetComponentType<MotionComponent>(),
       coordinator_->GetComponentType<CollisionComponent>()});

  serialization_system_ =
      coordinator_->RegisterSystem<SerializationSystem>(coordinator_.get(),
                                                        spawner_.get());
  coordinator_->SetSystemSignature<SerializationSystem>(
      {coordinator_->GetComponentType<SerializationComponent>()});

  death_system_ = coordinator_->RegisterSystem<DeathSystem>(
      coordinator_.get(), scene_.get());
  coordinator_->SetSystemSignature<DeathSystem>(
      {coordinator_->GetComponentType<HealthComponent>()});
}

void Connector::OnKeyPress(Qt::Key key) {
  keyboard_->OnPress(key);
}

void Connector::OnKeyRelease(Qt::Key key) {
  keyboard_->OnRelease(key);
}

void Connector::OnMousePress(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    spawner_->CreateBullet(
        player_.value(),
        helpers::WidgetToGameCoord(event->pos(), scene_->size()));
  }
}

const PixmapComponent& Connector::GetPixmapComponent(Entity entity) {
  return coordinator_->GetComponent<PixmapComponent>(entity);
}

const TransformationComponent& Connector::GetTransformComponent(Entity entity) {
  return coordinator_->GetComponent<TransformationComponent>(entity);
}

const std::unordered_set<Entity>& Connector::GetEntitiesToRender() const {
  return render_system_->entities_;
}

void Connector::ChangeRoom(const DoorComponent& component) {
  int32_t id = component.next_room_id;
  QVector2D pos = component.next_player_pos;

  scene_->StopTimer();

  serialization_system_->Serialize();
  serialization_system_->Deserialize(id);
  coordinator_->GetComponent<TransformationComponent>(player_.value()).pos =
      pos;

  scene_->StartTimer();
}

void Connector::LoadGame() {
  player_ = spawner_->CreatePlayer({0, 0});

  spawner_->CreateWalls();
  serialization_system_->SetDoors(spawner_->CreateDoors());
  serialization_system_->Deserialize(0);
}

void Connector::StartNewGame() {
  // TODO(Khody31 or Koshchanka) : Add map generation
}

std::shared_ptr<Scene> Connector::GetScene() {
  return scene_;
}

