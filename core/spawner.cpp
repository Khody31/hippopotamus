#include "spawner.h"

#include "components/components.h"
#include "constants.h"

Spawner::Spawner(Coordinator* coordinator) : coordinator_(coordinator) {
}

void Spawner::CreateBullet(Entity entity, const QVector2D& game_coord) {
  Entity bullet = coordinator_->CreateEntity();
  const QVector2D& entity_pos =
      coordinator_->GetComponent<TransformationComponent>(entity).pos;
  QVector2D direction = game_coord - entity_pos;

  coordinator_->AddComponent(bullet, TransformationComponent{entity_pos});
  coordinator_->AddComponent(bullet, MotionComponent{1.0f, direction});
  static QPixmap bullet_pixmap(":/textures/player.png");
  coordinator_->AddComponent(bullet, PixmapComponent{
      &bullet_pixmap,
      {0.1, 0.1}
  });
  coordinator_->AddComponent(bullet, CollisionComponent{
      1, 1, {0.1, 0.1}
  });
  coordinator_->AddComponent(bullet, DamageComponent{30});
  coordinator_->AddComponent(bullet, BulletComponent{});
}

void Spawner::CreateBall(const QVector2D& coordinates) {
  Entity ball = coordinator_->CreateEntity();
  coordinator_->AddComponent(ball, TransformationComponent{coordinates});
  coordinator_->AddComponent(ball, MotionComponent{1.0});
  static QPixmap ball_texture(":/textures/player.png");
  coordinator_->AddComponent(
      ball, PixmapComponent{&ball_texture, {0.2, 0.2}});
  coordinator_->AddComponent(ball, CollisionComponent{
      1, 1, {0.2, 0.2}});
  coordinator_->AddComponent(ball, SerializationComponent{EntityType::kBall});
  coordinator_->AddComponent(ball, HealthComponent{100});
  coordinator_->AddComponent(ball, IntelligenceComponent{});
}

void Spawner::CreateWall(const QVector2D& pos, const QVector2D& size) {
  Entity wall = coordinator_->CreateEntity();
  coordinator_->AddComponent(wall, TransformationComponent{pos});
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

Entity Spawner::CreatePlayer(const QVector2D& coordinates) {
  Entity player = coordinator_->CreateEntity();

  coordinator_->AddComponent(player, TransformationComponent{coordinates});
  coordinator_->AddComponent(player, MotionComponent{1.0});
  coordinator_->AddComponent(player, JoystickComponent{});
  static Animation animation
      ({":/textures/1.png", ":/textures/2.png", ":/textures/3.png",
        ":/textures/4.png"}, 100);
  static Animation left
      ({":/textures/test_1.png",
        ":/textures/test_2.png",
        ":/textures/test_3.png",
        ":/textures/test_4.png",
        ":/textures/test_5.png",
        ":/textures/test_6.png"}, 100);
  coordinator_->AddComponent(
      player, PixmapComponent{nullptr, {0.2, 0.2}});
  coordinator_->AddComponent(player,
                             AnimationComponent{AnimationComponent::kMoving,
                                                {&animation, &left,
                                                 &animation, &animation,
                                                 &animation}});
  coordinator_->AddComponent(player, CollisionComponent{
      1, 0, {0.2, 0.2}});
  coordinator_->AddComponent(player, HealthComponent{100});

  return player;
}

Entity Spawner::CreateDoor(const QVector2D& coordinates,
                           const QVector2D& size,
                           const QVector2D& player_pos) {
  Entity door = coordinator_->CreateEntity();
  coordinator_->AddComponent(door, TransformationComponent{coordinates});
  coordinator_->AddComponent(door, MotionComponent{0.0});

  static QPixmap door_pixmap(":/textures/player.png");
  coordinator_->AddComponent(door, PixmapComponent{&door_pixmap, size});
  coordinator_->AddComponent(door, CollisionComponent{
      0, 1, size});
  coordinator_->AddComponent(door, DoorComponent{1, player_pos});
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

void Spawner::CreateEntity(EntityType type, const QVector2D& pos) {
  switch (type) {
    case EntityType::kPlayer : {
      CreatePlayer(pos);
      break;
    }
    case EntityType::kWall : {
      CreateWalls();
      break;
    }
    case EntityType::kBall : {
      CreateBall(pos);
      break;
    }
    default: {
      return;
    }
  }
}
