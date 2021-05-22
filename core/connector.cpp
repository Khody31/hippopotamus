#include "connector.h"

#include "utility.h"

Connector::Connector(QWidget* parent, AbstractController* controller)
    : player_(std::make_unique<Entity>()),
      scene_(std::make_unique<Scene>(this,
                                     coordinator_.get(),
                                     controller,
                                     parent,
                                     player_.get()
      )),
      coordinator_(std::make_unique<Coordinator>()),
      keyboard_(std::make_unique<Keyboard>()),
      spawner_(std::make_unique<Spawner>(coordinator_.get())) {
  RegisterComponents();
  RegisterSystems();
  LoadGame();
}

void Connector::OnTick() {
  joystick_system_->Update();
  collision_system_->Update();
  movement_system_->Update();
  render_system_->Update();
  intelligence_system_->Update();
  // this system must be updated strictly last
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
  coordinator_->RegisterComponent<BulletComponent>();
  coordinator_->RegisterComponent<IntelligenceComponent>();
  coordinator_->RegisterComponent<WallComponent>();
  coordinator_->RegisterComponent<GarbageComponent>();
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
                                                        spawner_.get(),
                                                        player_.get());
  coordinator_->SetSystemSignature<SerializationSystem>(
      {coordinator_->GetComponentType<SerializationComponent>()});

  death_system_ =
      coordinator_->RegisterSystem<DeathSystem>(coordinator_.get(),
                                                scene_.get(),
                                                player_.get());

  coordinator_->SetSystemSignature<DeathSystem>(
      {coordinator_->GetComponentType<HealthComponent>()});

  intelligence_system_ = coordinator_->RegisterSystem<IntelligenceSystem>
      (collision_system_.get(),
       coordinator_.get(),
       player_.get(),
       keyboard_.get());
  coordinator_->SetSystemSignature<IntelligenceSystem>(
      {coordinator_->GetComponentType<IntelligenceComponent>(),
       coordinator_->GetComponentType<MotionComponent>(),
       coordinator_->GetComponentType<TransformationComponent>()});

  garbage_system_ =
      coordinator_->RegisterSystem<GarbageSystem>(coordinator_.get());
  coordinator_->SetSystemSignature<GarbageSystem>(
      {coordinator_->GetComponentType<GarbageComponent>()});
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
        *player_,
        utility::WidgetToGameCoord(event->pos(), scene_->size()));
  }
}

const std::unordered_set<Entity>& Connector::GetEntitiesToRender() const {
  return render_system_->entities_;
}

// Here DoorComponent is copied on purpose.
void Connector::ChangeRoom(DoorComponent door) {
  scene_->StopTimer();

  serialization_system_->Serialize();
  garbage_system_->Update();
  serialization_system_->Deserialize(door);

  scene_->StartTimer();
}

void Connector::LoadGame() {
  *player_ = spawner_->CreatePlayer({0, 0});
  spawner_->CreateWalls();
  serialization_system_->Deserialize({0});
}

void Connector::StartNewGame() {
  // TODO(Khody31 or Koshchanka) : Add map generation
}

Scene* Connector::GetScene() {
  return scene_.get();
}
