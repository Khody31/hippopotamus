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

void Spawner::CreateBall(const QVector2D& coordinates) {
  Entity ball = coordinator_->CreateEntity();

  coordinator_->AddComponent(ball, TransformationComponent{coordinates});
  coordinator_->AddComponent(ball, MotionComponent{1.0});
  coordinator_->AddComponent(
      ball, PixmapComponent{QPixmap(":/textures/player.png"), {0.2, 0.2}});
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
  coordinator_->AddComponent(
      player, PixmapComponent{QPixmap(":/textures/player.png"), {0.2, 0.2}});
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
  coordinator_->AddComponent(
      door, PixmapComponent{QPixmap(":/textures/player.png"), size});
  coordinator_->AddComponent(door, CollisionComponent{
      0, 1, size});
  coordinator_->AddComponent(door, DoorComponent{1, player_pos});

  return door;
}


Entity Spawner::CreateStupidBot(const QVector2D& pos) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{pos});
  coordinator_->AddComponent(enemy, MotionComponent{1.0});
  coordinator_->AddComponent(enemy,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             {0.1, 0.1}});
  coordinator_->AddComponent(enemy, CollisionComponent{
      1, 1, {0.1, 0.1}
  });
  coordinator_->AddComponent(enemy,
                             SerializationComponent{EntityType::kStupidBot});
  coordinator_->AddComponent(enemy,
                             IntelligenceComponent{IntelligenceType::kStupid});
  coordinator_->AddComponent(enemy, HealthComponent{200});

  return enemy;
}

Entity Spawner::CreateAngryPlant(const QVector2D& pos) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{pos});
  coordinator_->AddComponent(enemy, MotionComponent{1.0});
  coordinator_->AddComponent(enemy,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             {0.1, 0.1}});
  coordinator_->AddComponent(enemy, CollisionComponent{
      0, 1, {0.1, 0.1}
  });
  coordinator_->AddComponent(enemy,
                             SerializationComponent{EntityType::kAngryPlant});
  coordinator_->AddComponent(enemy,
                             IntelligenceComponent{
                                 IntelligenceType::kStanding});
  coordinator_->AddComponent(enemy, HealthComponent{100});

  return enemy;
}

Entity Spawner::CreateCleverBot(const QVector2D& pos) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{pos});
  coordinator_->AddComponent(enemy, MotionComponent{1.0});
  coordinator_->AddComponent(enemy,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             {0.1, 0.1}});
  coordinator_->AddComponent(enemy, CollisionComponent{
      1, 1, {0.1, 0.1}
  });
  coordinator_->AddComponent(enemy,
                             SerializationComponent{EntityType::kCleverBot});
  coordinator_->AddComponent(enemy,
                             IntelligenceComponent{IntelligenceType::kClever});
  coordinator_->AddComponent(enemy, HealthComponent{100});

  return enemy;
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
    case EntityType::kStupidBot : {
      CreateStupidBot(pos);
      break;
    }
    case EntityType::kAngryPlant : {
      CreateAngryPlant(pos);
      break;
    }
    case EntityType::kCleverBot : {
      CreateCleverBot(pos);
      break;
    }
    default: {
      return;
    }
  }
}
