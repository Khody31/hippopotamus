#include "spawner.h"
#include "engine/coordinator.h"
#include "components/components.h"
#include "game_constants.h"

Entity Spawner::CreateBulletFor(Entity entity, const QVector2D& game_coord) {
  Entity bullet = coordinator_->CreateEntity();
  const QVector2D& entity_pos =
      coordinator_->GetComponent<TransformationComponent>(entity).pos;
  QVector2D direction = game_coord - entity_pos;
  coordinator_->AddComponent(bullet, TransformationComponent{entity_pos});
  coordinator_->AddComponent(bullet, MotionComponent{0.15f, direction});
  coordinator_->AddComponent(bullet, PixmapComponent{
      QPixmap(":/player.png"),
      {0.1, 0.1}
  });
  return bullet;
}

Spawner::Spawner(Coordinator* coordinator) :
    coordinator_(coordinator) {
}

Entity Spawner::CreateBall(const QVector2D& coordinates) {
  Entity ball = coordinator_->CreateEntity();
  coordinator_->AddComponent(ball, TransformationComponent{coordinates});
  coordinator_->AddComponent(ball, MotionComponent{1.0});
  coordinator_->AddComponent(ball,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             {0.2, 0.2}});
  coordinator_->AddComponent(ball, CollisionComponent{
    1, 1, {0.2, 0.2}
  });
  coordinator_->AddComponent(ball, SerializationComponent{EntityType::kBall});
  coordinator_->AddComponent(ball, AiComponent{AiType::kStupid});
  return ball;
}

Entity Spawner::CreateWall(const QVector2D& pos, const QVector2D& size) {
  Entity wall = coordinator_->CreateEntity();
  coordinator_->AddComponent(wall, TransformationComponent{pos});
  coordinator_->AddComponent(wall, MotionComponent{1.0});
  coordinator_->AddComponent(wall, CollisionComponent{
    0, 1, size});
  return wall;
}

std::array<Entity, 4> Spawner::CreateWalls() {
  return {
    CreateWall({0, 1}, {3.2, 0.2}),
    CreateWall({0, -1}, {3.2, 0.2}),
    CreateWall({-1.7, 0.0}, {0.2, 1.8}),
    CreateWall({1.7, 0.0}, {0.2, 1.8})
  };
}

Entity Spawner::CreatePlayer(const QVector2D& coordinates) {
  Entity player = coordinator_->CreateEntity();
  coordinator_->AddComponent(player, TransformationComponent{coordinates});
  coordinator_->AddComponent(player, MotionComponent{1.0});
  coordinator_->AddComponent(player, JoystickComponent{});
  coordinator_->AddComponent(player,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             {0.2, 0.2}});
  coordinator_->AddComponent(player, CollisionComponent{
      1, 0, {0.2, 0.2}, CollisionType::kPlayer
  });
  return player;
}

Entity Spawner::CreateDoor(const QVector2D& coordinates,
                           const QVector2D& size) {
  Entity door = coordinator_->CreateEntity();
  coordinator_->AddComponent(door, TransformationComponent{coordinates});
  coordinator_->AddComponent(door, MotionComponent{0.0});
  coordinator_->AddComponent(door,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             size});
  coordinator_->AddComponent(door, CollisionComponent{
    0, 1, size, CollisionType::kRoomChanging
  });
  coordinator_->AddComponent(door, DoorComponent{1, {0, -0.7}});
  return door;
}

std::array<Entity, 4> Spawner::CreateDoors() {
  std::array<Entity, 4> doors{};

  doors.at(0) = CreateDoor(game_constants::kTopDoorCoordinates,
                           game_constants::kHorizontalDoorSize);
  coordinator_->GetComponent<DoorComponent>(doors.at(0)).next_player_pos =
      game_constants::kPosToMovePlayerTop;

  doors.at(1) = CreateDoor(game_constants::kRightDoorCoordinates,
                           game_constants::kVerticalDoorSize);
  coordinator_->GetComponent<DoorComponent>(doors.at(1)).next_player_pos =
      game_constants::kPosToMovePlayerRight;

  doors.at(2) = CreateDoor(game_constants::kBottomDoorCoordinates,
                           game_constants::kHorizontalDoorSize);
  coordinator_->GetComponent<DoorComponent>(doors.at(2)).next_player_pos =
      game_constants::kPosToMovePlayerBottom;

  doors.at(3) = CreateDoor(game_constants::kLeftDoorCoordinates,
                           game_constants::kVerticalDoorSize);
  coordinator_->GetComponent<DoorComponent>(doors.at(3)).next_player_pos =
      game_constants::kPosToMovePlayerLeft;

  return doors;
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
    case EntityType::kDoor : {
      CreateDoor(pos, game_constants::kVerticalDoorSize);
      break;
    }
    default: {
      throw "Unknown entity";
    }
  }
}
