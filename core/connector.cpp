#include <memory>
#include <unordered_set>

#include "helpers.h"
#include "connector.h"
#include "game_scene.h"

Connector::Connector() {
  RegisterComponents();
  RegisterSystems();

  spawner_ = std::make_shared<Spawner>(&coordinator_);
  LoadGame();
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

  std::array<uint32_t, 4> connected_rooms;
  for (int i = 0; i < 4; ++i) {
    connected_rooms[i] =
        coordinator_.GetComponent<DoorComponent>(doors_[i]).next_room_id;
  }

  serialization_system->Serialize(&coordinator_,
                                  current_room_id_,
                                  connected_rooms);
  serialization_system->Deserialize(&coordinator_,
                                    id,
                                    spawner_.get(),
                                    &connected_rooms);

  current_room_id_ = id;
  for (int i = 0; i < 4; ++i) {
    coordinator_.GetComponent<DoorComponent>(doors_[i]).next_room_id
        = connected_rooms[i];
  }

  UpdateDoors();

  coordinator_.GetComponent<TransformationComponent>(player_).pos = pos;
  scene_->StartTimer();
}

void Connector::LoadGame() {
  Entity player = spawner_->CreatePlayer({0, 0});
  SetPlayer(player);

  spawner_->CreateWalls();
  doors_ = spawner_->CreateDoors();

  std::array<uint32_t, 4> connected_rooms;
  serialization_system->Deserialize(&coordinator_,
                                    0,
                                    spawner_.get(),
                                    &connected_rooms);
  current_room_id_ = 0;
  for (int i = 0; i < 4; ++i) {
    coordinator_.GetComponent<DoorComponent>(doors_[i]).next_room_id =
        connected_rooms[i];
  }
  UpdateDoors();
}

void Connector::StartNewGame() {
  // TODO(Khody31 or Koshchanka) : Add map generation
}

void Connector::UpdateDoors() {
  for (int i = 0; i < 4; ++i) {
    uint32_t door = doors_[i];
    if (coordinator_.GetComponent<DoorComponent>(door).next_room_id == -1) {
      coordinator_.RemoveComponent<PixmapComponent>(door);
      coordinator_.RemoveComponent<CollisionComponent>(door);
    } else {
      QVector2D size = (i % 2 == 1) ? game_constants::kHorizontalDoorSize
                                    : game_constants::kVerticalDoorSize;
      if (!coordinator_.HasComponent<PixmapComponent>(door)) {
        QPixmap pixmap(":/textures/player.png");

        coordinator_.AddComponent<PixmapComponent>(
            door,
            PixmapComponent{pixmap, size});
      }
      if (!coordinator_.HasComponent<CollisionComponent>(door)) {

        coordinator_.AddComponent<CollisionComponent>(door,CollisionComponent{CollisionType::kRoomChanging, 0, 0, size});
      }
    }
  }
}

