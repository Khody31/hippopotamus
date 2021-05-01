#include <memory>

#include "coordinates_helpers.h"
#include "connector.h"
#include "game_scene.h"

Connector::Connector() {
  RegisterComponents();
  RegisterSystems();

  spawner_ = std::make_shared<Spawner>(&coordinator_);

  Entity player = spawner_->CreatePlayer();
  SetPlayer(player);

  spawner_->CreateBall();
  spawner_->CreateWall();
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
}

void Connector::OnKeyPress(Qt::Key key) {
  keyboard_interface_.OnPress(key);
}

void Connector::OnKeyRelease(Qt::Key key) {
  keyboard_interface_.OnRelease(key);
}

void Connector::OnMousePress(QMouseEvent* event) {
  QVector2D scene_size = QVector2D(static_cast<float>(scene_->width()),
                                   static_cast<float>(scene_->height()));
  if (event->button() == Qt::LeftButton) {
    spawner_->CreateBulletFor(
        player_,
        coordinates_helpers::WidgetToGameCoord(event->pos(), scene_size));
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
