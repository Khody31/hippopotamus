#include <vector>
#include <limits>

#include "connector.h"
#include "components/components.h"
#include "constants.h"
#include "spawner.h"

Spawner::Spawner(Coordinator* coordinator, Connector* connector, Entity* player)
    : coordinator_(coordinator), connector_(connector), player_(player) {}

void Spawner::CreateBullet(Entity entity, const QVector2D& destination) {
  static QPixmap default_pixmap = QPixmap(":/textures/bullet-small.png");

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
      static QPixmap pixmap = QPixmap(":/textures/bullet-medium.png");
      coordinator_->AddComponent(bullet, PixmapComponent{
          {0.13, 0.13}, &pixmap});
      coordinator_->AddComponent(bullet, DamageComponent{30});
      coordinator_->AddComponent(
          bullet, BulletComponent{BulletType::kStrongStone, entity});
      coordinator_->AddComponent(bullet, MotionComponent{3.0, direction});
      return;
    }
    if (buff_to_time[BuffType::kFireball]) {
      connector_->PlaySound(GameSound::kFireball);
      static QPixmap pixmap = QPixmap(":/textures/bullet-big.png");
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
      player, PixmapComponent{{0.2, 0.2}});
  static AnimationPack animation_pack = AnimationPack(":/animations/demo.json");
  coordinator_->AddComponent(
      player, AnimationComponent{AnimationPackType::kMoving, &animation_pack});
  coordinator_->AddComponent(player, CollisionComponent{1, 0, {0.2, 0.2}});
  coordinator_->AddComponent(player, HealthComponent{10000});
  coordinator_->AddComponent(
      player, StateComponent{std::vector<int32_t>(BuffType::kEnumSize, 0)});
  return player;
}

Entity Spawner::CreateLittleSkeleton(const QVector2D& spawn_pos) {
  Entity enemy = coordinator_->CreateEntity();

  constexpr QVector2D size{0.15, 0.15};

  coordinator_->AddComponent(enemy, TransformationComponent{spawn_pos});
  coordinator_->AddComponent(enemy, MotionComponent{0.5});
  static QPixmap pixmap = QPixmap(":/textures/skeleton.png");
  coordinator_->AddComponent(enemy, PixmapComponent{size, &pixmap});
  coordinator_->AddComponent(enemy, CollisionComponent{1, 10, size});
  coordinator_->AddComponent(enemy,
                             SerializationComponent{
                                 EntityType::kLittleSkeleton});
  coordinator_->AddComponent(enemy,
                             IntelligenceComponent{
                                 IntelligenceType::kClever});
  coordinator_->AddComponent(enemy, HealthComponent{40});
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

  const QVector2D size = QVector2D{0.9, 1.2};

  coordinator_->AddComponent(enemy, TransformationComponent{QVector2D{0, 0}});
  coordinator_->AddComponent(enemy, MotionComponent{0.0});
  coordinator_->AddComponent(enemy, PixmapComponent{size});
  static AnimationPack
      animation = AnimationPack(":/animations/necromancer.json");
  coordinator_->AddComponent(
      enemy, AnimationComponent{AnimationPackType::kStatic, &animation});
  coordinator_->AddComponent(enemy, CollisionComponent{0, 1, size * 0.4});
  coordinator_->AddComponent(enemy,
                             SerializationComponent{EntityType::kNecromancer});
  coordinator_->AddComponent(
      enemy, IntelligenceComponent{IntelligenceType::kReproductive});
  coordinator_->AddComponent(enemy, HealthComponent{10000});
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
                             IntelligenceComponent{
                                 IntelligenceType::kShooting});
  coordinator_->AddComponent(enemy, HealthComponent{1000});
  coordinator_->AddComponent(enemy, DamageComponent{100});
  coordinator_->AddComponent(
      enemy, StateComponent{std::vector<int32_t>(EnemyState::kEnumSize, 0)});
  return enemy;
}

Entity Spawner::CreateDoor(const QVector2D& coordinates,
                           const QVector2D& size,
                           const QVector2D& player_position,
                           int32_t associated_room,
                           QPixmap* pixmap,
                           SceneLayers layer) {
  Entity door = coordinator_->CreateEntity();
  if (associated_room == -1) {
    coordinator_->AddComponent(door, DoorComponent{-1});
    return door;
  }
  coordinator_->AddComponent(door, MotionComponent{0.0});
  coordinator_->AddComponent(door, TransformationComponent{coordinates});
  coordinator_->AddComponent(
      door, PixmapComponent{size, pixmap, layer});
  coordinator_->AddComponent(door, CollisionComponent{0, 1, size});
  coordinator_->AddComponent(
      door, DoorComponent{associated_room, player_position});
  coordinator_->AddComponent(door, GarbageComponent{});

  return door;
}

void Spawner::CreateDoors(const std::array<int32_t, 4>& rooms) {
  static QPixmap top_door_pixmap = QPixmap(":/textures/top-door.png");
  CreateDoor(constants::kTopDoorCoordinates,
             constants::kTopDoorSize,
             constants::kPosToMovePlayerTop,
             rooms[0],
             &top_door_pixmap,
             SceneLayers::kDoors);

  static QPixmap right_door_pixmap = QPixmap(":/textures/right-door.png");
  CreateDoor(constants::kRightDoorCoordinates,
             constants::kVerticalDoorSize,
             constants::kPosToMovePlayerRight,
             rooms[1],
             &right_door_pixmap,
             SceneLayers::kDoors);

  static QPixmap bottom_door_pixmap = QPixmap(":/textures/bottom-door.png");
  CreateDoor(constants::kBottomDoorCoordinates,
             constants::kBottomDoorSize,
             constants::kPosToMovePlayerBottom,
             rooms[2],
             &bottom_door_pixmap,
             SceneLayers::kBottomDoor);

  static QPixmap left_door_pixmap = QPixmap(":/textures/left-door.png");
  CreateDoor(constants::kLeftDoorCoordinates,
             constants::kVerticalDoorSize,
             constants::kPosToMovePlayerLeft,
             rooms[3],
             &left_door_pixmap,
             SceneLayers::kDoors);
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
    case EntityType::kDecorative1:
    case EntityType::kDecorative2:
    case EntityType::kDecorative3:
    case EntityType::kDecorative4:
    case EntityType::kDecorative5:
    case EntityType::kDecorative6:
    case EntityType::kDecorative7:
    case EntityType::kDecorative8:
    case EntityType::kDecorative9:
    case EntityType::kDecorative10:
    case EntityType::kDecorative11:
    case EntityType::kDecorative12:
    case EntityType::kDecorative13:
    case EntityType::kDecorative14:
    case EntityType::kDecorative15: {
      CreateDecor(type, position);
      break;
    }
    case EntityType::kPile1:
    case EntityType::kPile2:
    case EntityType::kPile3:
    case EntityType::kPile4:
    case EntityType::kPile5: {
      CreatePile(type, position);
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

void Spawner::CreateBackground() {
  static QPixmap pixmap(":/textures/room-base.png");
  Entity floor = coordinator_->CreateEntity();
  coordinator_->AddComponent(floor, TransformationComponent{});
  coordinator_->AddComponent(
      floor,
      PixmapComponent{QVector2D(3.2, 1.8), &pixmap, SceneLayers::kBackground});
}

void Spawner::CreateDecor(EntityType type, const QVector2D& position) {
  Entity decor = coordinator_->CreateEntity();
  static const std::vector<QPixmap> pixmaps{
      QPixmap(":/textures/decor1.png"),
      QPixmap(":/textures/decor2.png"),
      QPixmap(":/textures/decor3.png"),
      QPixmap(":/textures/decor4.png"),
      QPixmap(":/textures/decor5.png"),
      QPixmap(":/textures/decor6.png"),
      QPixmap(":/textures/decor7.png"),
      QPixmap(":/textures/decor8.png"),
      QPixmap(":/textures/decor9.png"),
      QPixmap(":/textures/decor10.png"),
      QPixmap(":/textures/decor11.png"),
      QPixmap(":/textures/decor12.png"),
      QPixmap(":/textures/decor13.png"),
      QPixmap(":/textures/decor14.png"),
      QPixmap(":/textures/decor15.png"),
  };

  int32_t decor_num = static_cast<int32_t>(type) -
      static_cast<int32_t>(EntityType::kDecorative1);
  coordinator_->AddComponent(decor, PixmapComponent{
      {0.2, 0.2}, &pixmaps[decor_num], SceneLayers::kDecor});

  coordinator_->AddComponent(decor, SerializationComponent{type});
  coordinator_->AddComponent(decor, TransformationComponent{position});
}

void Spawner::CreatePile(EntityType type, const QVector2D& position) {
  Entity pile = coordinator_->CreateEntity();
  static const std::vector<QPixmap> pixmaps{
      QPixmap(":/textures/pile1.png"),
      QPixmap(":/textures/pile2.png"),
      QPixmap(":/textures/pile3.png"),
      QPixmap(":/textures/pile4.png"),
      QPixmap(":/textures/pile5.png"),
  };

  int32_t decor_num = static_cast<int32_t>(type) -
      static_cast<int32_t>(EntityType::kPile1);
  coordinator_->AddComponent(pile, PixmapComponent{
      {0.35, 0.35}, &pixmaps[decor_num]});
  coordinator_->AddComponent(pile, CollisionComponent{
      0, 1, {0.15, 0.15}});

  coordinator_->AddComponent(pile, SerializationComponent{type});
  coordinator_->AddComponent(pile, TransformationComponent{position});
  coordinator_->AddComponent(pile, MotionComponent{0});
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
