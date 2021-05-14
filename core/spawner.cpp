#include "spawner.h"
#include "engine/coordinator.h"
#include "components/components.h"
#include "constants.h"

Spawner::Spawner(Coordinator* coordinator) : coordinator_(coordinator) {
}

void Spawner::CreateBullet(Entity entity, const QVector2D& cursor_position) {
  Entity bullet = coordinator_->CreateEntity();
  const QVector2D& entity_position =
      coordinator_->GetComponent<TransformationComponent>(entity).pos;
  QVector2D direction = cursor_position - entity_position;

  coordinator_->AddComponent(bullet, TransformationComponent{entity_position});
  coordinator_->AddComponent(bullet, MotionComponent{1.0f, direction});
  coordinator_->AddComponent(bullet, PixmapComponent{
      QPixmap(":/textures/player.png"),
      {0.1, 0.1}
  });
  coordinator_->AddComponent(bullet, CollisionComponent{
      1, 1, {0.1, 0.1}
  });
  coordinator_->AddComponent(bullet, DamageComponent{30});
  coordinator_->AddComponent(bullet, BulletComponent{});
}

void Spawner::CreateBall(const QVector2D& position) {
  Entity ball = coordinator_->CreateEntity();
  coordinator_->AddComponent(ball, TransformationComponent{position});
  coordinator_->AddComponent(ball, MotionComponent{1.0});
  coordinator_->AddComponent(
      ball, PixmapComponent{QPixmap(":/textures/player.png"), {0.2, 0.2}});
  coordinator_->AddComponent(ball, CollisionComponent{
      1, 1, {0.2, 0.2}});
  coordinator_->AddComponent(ball, SerializationComponent{EntityType::kBall});
  coordinator_->AddComponent(ball, HealthComponent{100});
  coordinator_->AddComponent(ball, IntelligenceComponent{});
}

void Spawner::CreateWall(const QVector2D& position, const QVector2D& size) {
  Entity wall = coordinator_->CreateEntity();
  coordinator_->AddComponent(wall, TransformationComponent{position});
  coordinator_->AddComponent(wall, MotionComponent{0});
  coordinator_->AddComponent(wall, CollisionComponent{
      0, 1, size});
}

void Spawner::CreateWalls() {
  CreateWall(constants::kTopWallCoordinates,
             constants::kHorizontalWallSize);
  CreateWall(constants::kBottomWallCoordinates,
             constants::kHorizontalWallSize);
  CreateWall(constants::kRightWallCoordinates,
             constants::kVerticalWallSize);
  CreateWall(constants::kLeftWallCoordinates,
             constants::kVerticalWallSize);
}

Entity Spawner::CreatePlayer(const QVector2D& position) {
  Entity player = coordinator_->CreateEntity();

  coordinator_->AddComponent(player, TransformationComponent{position});
  coordinator_->AddComponent(player, MotionComponent{1.0});
  coordinator_->AddComponent(player, JoystickComponent{});
  coordinator_->AddComponent(
      player, PixmapComponent{QPixmap(":/textures/player.png"), {0.2, 0.2}});
  coordinator_->AddComponent(player, CollisionComponent{
      1, 0, {0.2, 0.2}});
  coordinator_->AddComponent(player, HealthComponent{100});

  return player;
}

Entity Spawner::CreateDoor(const QVector2D& position,
                           const QVector2D& size,
                           const QVector2D& player_position) {
  Entity door = coordinator_->CreateEntity();
  coordinator_->AddComponent(door, TransformationComponent{position});
  coordinator_->AddComponent(door, MotionComponent{0.0});
  coordinator_->AddComponent(
      door, PixmapComponent{QPixmap(":/textures/player.png"), size});
  coordinator_->AddComponent(door, CollisionComponent{
      0, 1, size});
  coordinator_->AddComponent(door, DoorComponent{1, player_position});
  return door;
}

std::array<Entity, 4> Spawner::CreateDoors() {
  return {CreateDoor(constants::kTopDoorCoordinates,
                     constants::kHorizontalDoorSize,
                     constants::kPosToMovePlayerTop),
          CreateDoor(constants::kRightDoorCoordinates,
                     constants::kVerticalDoorSize,
                     constants::kPosToMovePlayerRight),
          CreateDoor(constants::kBottomDoorCoordinates,
                     constants::kHorizontalDoorSize,
                     constants::kPosToMovePlayerBottom),
          CreateDoor(constants::kLeftDoorCoordinates,
                     constants::kVerticalDoorSize,
                     constants::kPosToMovePlayerLeft)};
}

void Spawner::CreateEntity(EntityType type, const QVector2D& position) {
  switch (type) {
    case EntityType::kPlayer : {
      CreatePlayer(position);
      break;
    }
    case EntityType::kWall : {
      CreateWalls();
      break;
    }
    case EntityType::kBall : {
      CreateBall(position);
      break;
    }
    default: {
      return;
    }
  }
}
