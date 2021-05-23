#include <vector>

#include "connector.h"
#include "components/components.h"
#include "constants.h"
#include "spawner.h"

Spawner::Spawner(Coordinator* coordinator, Connector* connector, Entity* player)
    : coordinator_(coordinator), connector_(connector), player_(player) {}

void Spawner::CreateBullet(Entity entity, const QVector2D& destination) {
  static QPixmap default_pixmap = QPixmap(":/textures/player.png");

  Entity bullet = coordinator_->CreateEntity();

  QVector2D position =
      coordinator_->GetComponent<TransformationComponent>(entity).position;
  QVector2D direction = destination - position;

  coordinator_->AddComponent(bullet, TransformationComponent{position});
  coordinator_->AddComponent(bullet, CollisionComponent{1, 1, {0.1, 0.1}});
  coordinator_->AddComponent(bullet, GarbageComponent{});

  if (entity == *player_) {
    connector_->PlaySound(GameSound::kPlayerShoot);
    const std::vector<int32_t>& buff_to_time = connector_->GetPlayerBuff();
    if (buff_to_time[BuffType::kStrongStone]) {
      static QPixmap pixmap = QPixmap(":/textures/stone.png");
      coordinator_->AddComponent(bullet, PixmapComponent{
        {0.10, 0.10}, &pixmap});
      coordinator_->AddComponent(bullet, DamageComponent{30});
      coordinator_->AddComponent(
          bullet, BulletComponent{BulletType::kStrongStone, entity});
      coordinator_->AddComponent(bullet, MotionComponent{3.0, direction});
      return;
    }
    if (buff_to_time[BuffType::kFireball]) {
      connector_->PlaySound(GameSound::kFireball);
      static QPixmap pixmap = QPixmap(":/textures/fireball.png");
      coordinator_->AddComponent(bullet, PixmapComponent{
        {0.15, 0.15}, &pixmap});
      coordinator_->AddComponent(bullet, DamageComponent{50});
      coordinator_->AddComponent(
          bullet, BulletComponent{BulletType::kFireball, entity});
      coordinator_->AddComponent(bullet, MotionComponent{5.0, direction});
      return;
    }
  }
    connector_->PlaySound(GameSound::kPlayerShoot);
    coordinator_->AddComponent(bullet, PixmapComponent{
          {0.10, 0.10}, &default_pixmap});
    coordinator_->AddComponent(bullet, DamageComponent{15});
    coordinator_->AddComponent(
        bullet, BulletComponent{BulletType::kStone, entity});
    coordinator_->AddComponent(bullet, MotionComponent{1.0, direction});
}

void Spawner::CreateBall(const QVector2D& position) {
  Entity ball = coordinator_->CreateEntity();

  coordinator_->AddComponent(ball, TransformationComponent{position});
  coordinator_->AddComponent(ball, MotionComponent{1.0});
  static QPixmap pixmap = QPixmap(":/textures/player.png");
  coordinator_->AddComponent(
      ball, PixmapComponent{{0.2, 0.2}, &pixmap});
  coordinator_->AddComponent(ball, CollisionComponent{1, 1, {0.2, 0.2}});
  coordinator_->AddComponent(ball, SerializationComponent{EntityType::kBall});
  coordinator_->AddComponent(ball, HealthComponent{100});
}

void Spawner::CreateWall(const QVector2D& pos, const QVector2D& size) {
  Entity wall = coordinator_->CreateEntity();

  coordinator_->AddComponent(wall, TransformationComponent{pos});
  coordinator_->AddComponent(wall, MotionComponent{0.0});
  coordinator_->AddComponent(wall, CollisionComponent{0, 1, size});
  coordinator_->AddComponent(wall, WallComponent{});
}

void Spawner::CreateWalls() {
  CreateWall(constants::kTopWallCoordinates, constants::kHorizontalWallSize);
  CreateWall(constants::kBottomWallCoordinates, constants::kHorizontalWallSize);
  CreateWall(constants::kRightWallCoordinates, constants::kVerticalWallSize);
  CreateWall(constants::kLeftWallCoordinates, constants::kVerticalWallSize);
}

Entity Spawner::CreatePlayer(const QVector2D& position) {
  Entity player = coordinator_->CreateEntity();

  coordinator_->AddComponent(player, TransformationComponent{position});
  coordinator_->AddComponent(player, MotionComponent{1.0});
  coordinator_->AddComponent(player, JoystickComponent{});
  coordinator_->AddComponent(
      player, PixmapComponent{{0.2, 0.2}, nullptr});
  static AnimationPack animation_pack = AnimationPack(":/animations/demo.json");
  coordinator_->AddComponent(
      player, AnimationComponent{AnimationPackType::kMoving, &animation_pack});
  coordinator_->AddComponent(player, CollisionComponent{1, 0, {0.2, 0.2}});
  coordinator_->AddComponent(player, HealthComponent{100});
  coordinator_->AddComponent(
      player, StateComponent{std::vector<int32_t>(BuffType::kEnumSize, 0)});

  return player;
}

Entity Spawner::CreateLittleSkeleton(const QVector2D& pos) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{pos});
  coordinator_->AddComponent(enemy, MotionComponent{0.5});
  static QPixmap pixmap = QPixmap(":/textures/skeleton.png");
  coordinator_->AddComponent(enemy, PixmapComponent{{0.05, 0.05}, &pixmap});
  coordinator_->AddComponent(enemy, CollisionComponent{1, 10, {0.05, 0.05}});
  coordinator_->AddComponent(enemy,
                    SerializationComponent{EntityType::kLittleSkeleton});
  coordinator_->AddComponent(enemy,
                             IntelligenceComponent{IntelligenceType::kClever});
  coordinator_->AddComponent(enemy, HealthComponent{1});
  coordinator_->AddComponent(enemy, DamageComponent{1});
  coordinator_->AddComponent(
      enemy, StateComponent{std::vector<int32_t>(EnemyState::kEnumSize, 0)});
  return enemy;
}

Entity Spawner::CreateSmellingPlant(const QVector2D& pos) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{pos});
  coordinator_->AddComponent(enemy, MotionComponent{0.0});
  static QPixmap pixmap = QPixmap(":/textures/plant.png");
  coordinator_->AddComponent(enemy, PixmapComponent{{0.1, 0.1}, &pixmap});
  coordinator_->AddComponent(enemy, CollisionComponent{0, 1, {0.1, 0.1}});
  coordinator_->AddComponent(
      enemy, SerializationComponent{EntityType::kSmellingPlant});
  coordinator_->AddComponent(
      enemy, IntelligenceComponent{IntelligenceType::kEmitting});
  coordinator_->AddComponent(enemy, HealthComponent{100});
  coordinator_->AddComponent(enemy, DamageComponent{1});
  coordinator_->AddComponent(
      enemy, StateComponent{std::vector<int32_t>(EnemyState::kEnumSize, 0)});
  return enemy;
}

Entity Spawner::CreateAngryPlant(const QVector2D& position) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{position});
  static QPixmap pixmap = QPixmap(":/textures/player.png");
  coordinator_->AddComponent(
      enemy, PixmapComponent{{0.1, 0.1}, &pixmap});
  coordinator_->AddComponent(enemy, CollisionComponent{0, 1, {0.1, 0.1}});
  coordinator_->AddComponent(
      enemy, SerializationComponent{EntityType::kAngryPlant});
  coordinator_->AddComponent(enemy, MotionComponent{0.0});
  coordinator_->AddComponent(
      enemy, IntelligenceComponent{IntelligenceType::kRepulsive});
  coordinator_->AddComponent(enemy, HealthComponent{100});
  coordinator_->AddComponent(enemy, DamageComponent{5});
  coordinator_->AddComponent(
      enemy, StateComponent{std::vector<int32_t>(EnemyState::kEnumSize, 0)});
  return enemy;
}

Entity Spawner::CreateCleverBot(const QVector2D& position) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{position});
  coordinator_->AddComponent(enemy, MotionComponent{0.5});
  static QPixmap pixmap = QPixmap(":/textures/wasp.png");
  coordinator_->AddComponent(enemy, PixmapComponent{{0.2, 0.2}, &pixmap});
  coordinator_->AddComponent(enemy, CollisionComponent{1, 1, {0.1, 0.1}});
  coordinator_->AddComponent(
      enemy, SerializationComponent{EntityType::kCleverBot});
  coordinator_->AddComponent(
      enemy, IntelligenceComponent{IntelligenceType::kClever});
  coordinator_->AddComponent(enemy, HealthComponent{100});
  coordinator_->AddComponent(enemy, DamageComponent{1});
  coordinator_->AddComponent(
      enemy, StateComponent{std::vector<int32_t>(EnemyState::kEnumSize, 0)});
  return enemy;
}

Entity Spawner::CreateNecromancer(const QVector2D& pos) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{pos});
  coordinator_->AddComponent(enemy, MotionComponent{0.0});
  static QPixmap pixmap = QPixmap(":/textures/necromancer.png");
  coordinator_->AddComponent(enemy, PixmapComponent{{0.25, 0.25}, &pixmap});
  coordinator_->AddComponent(enemy, CollisionComponent{0, 1, {0.25, 0.25}});
  coordinator_->AddComponent(enemy,
                             SerializationComponent{EntityType::kNecromancer});
  coordinator_->AddComponent(enemy,
                IntelligenceComponent{IntelligenceType::kReproductive});
  coordinator_->AddComponent(enemy, HealthComponent{1000});
  coordinator_->AddComponent(enemy, DamageComponent{100});
  coordinator_->AddComponent(
      enemy, StateComponent{std::vector<int32_t>(EnemyState::kEnumSize, 0)});
  return enemy;
}

Entity Spawner::CreateShootingBoss(const QVector2D& pos) {
  Entity enemy = coordinator_->CreateEntity();

  coordinator_->AddComponent(enemy, TransformationComponent{pos});
  coordinator_->AddComponent(enemy, MotionComponent{0.5});
  static QPixmap pixmap = QPixmap(":/textures/player.png");
  coordinator_->AddComponent(enemy, PixmapComponent{{0.25, 0.25}, &pixmap});
  coordinator_->AddComponent(enemy, CollisionComponent{1, 1, {0.25, 0.25}});
  coordinator_->AddComponent(enemy,
                             SerializationComponent{EntityType::kShootingBoss});
  coordinator_->AddComponent(enemy,
                            IntelligenceComponent{IntelligenceType::kShooting});
  coordinator_->AddComponent(enemy, HealthComponent{1000});
  coordinator_->AddComponent(enemy, DamageComponent{100});
  coordinator_->AddComponent(
      enemy, StateComponent{std::vector<int32_t>(EnemyState::kEnumSize, 0)});
  return enemy;
}

Entity Spawner::CreateDoor(const QVector2D& coordinates,
                           const QVector2D& size,
                           const QVector2D& player_position,
                           int32_t associated_room) {
  Entity door = coordinator_->CreateEntity();

  if (associated_room == -1) {
    coordinator_->AddComponent(door, DoorComponent{-1});
    return door;
  }

  coordinator_->AddComponent(door, MotionComponent{0.0});
  coordinator_->AddComponent(door, TransformationComponent{coordinates});
  static QPixmap pixmap = QPixmap(":/textures/player.png");
  coordinator_->AddComponent(door, PixmapComponent{size, &pixmap});
  coordinator_->AddComponent(door, CollisionComponent{0, 1, size});
  coordinator_->AddComponent(
      door, DoorComponent{associated_room, player_position});
  coordinator_->AddComponent(door, GarbageComponent{});

  return door;
}

void Spawner::CreateDoors(const std::array<int32_t, 4>& rooms) {
  CreateDoor(constants::kTopDoorCoordinates,
             constants::kHorizontalDoorSize,
             constants::kPosToMovePlayerTop,
             rooms[0]);

  CreateDoor(constants::kRightDoorCoordinates,
             constants::kVerticalDoorSize,
             constants::kPosToMovePlayerRight,
             rooms[1]);

  CreateDoor(constants::kBottomDoorCoordinates,
             constants::kHorizontalDoorSize,
             constants::kPosToMovePlayerBottom,
             rooms[2]);

  CreateDoor(constants::kLeftDoorCoordinates,
             constants::kVerticalDoorSize,
             constants::kPosToMovePlayerLeft,
             rooms[3]);
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
    case EntityType::kLittleSkeleton : {
      CreateLittleSkeleton(position);
      break;
    }
    case EntityType::kAngryPlant : {
      CreateAngryPlant(position);
      break;
    }
    case EntityType::kCleverBot : {
      CreateCleverBot(position);
      break;
    }
    case EntityType::kSmellingPlant : {
      CreateSmellingPlant(position);
      break;
    }
    case EntityType::kNecromancer : {
      CreateNecromancer(position);
      break;
    }
    case EntityType::kShootingBoss : {
      CreateShootingBoss(position);
      break;
    }
    default: {
      return;
    }
  }
}

Entity Spawner::CreateArtifact(const QVector2D& position,
                               BuffType::Buff buff_type) {
  Entity artifact = coordinator_->CreateEntity();
  coordinator_->AddComponent(artifact, GarbageComponent{});
  coordinator_->AddComponent(artifact, TransformationComponent{position});
  static QPixmap pixmap{":/textures/peach.png"};
  coordinator_->AddComponent(artifact, PixmapComponent{
    constants::kArtifactSize, &pixmap});
  coordinator_->AddComponent(artifact, CollisionComponent{
      1, 0, constants::kArtifactSize});
  coordinator_->AddComponent(artifact, MotionComponent{0, {1, 1}});
  coordinator_->AddComponent(artifact, ArtifactComponent{buff_type, 0});
  return artifact;
}
