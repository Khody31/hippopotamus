#include "spawner.h"
#include "engine/coordinator.h"
#include "components/components.h"

#include <QDebug>

void Spawner::CreateBulletFor(Entity entity, const QVector2D& game_coord) {
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
}

Spawner::Spawner(Coordinator* coordinator) :
    coordinator_(coordinator) {
}

void Spawner::CreateBall(const QVector2D& coordinates) {
  Entity ball = coordinator_->CreateEntity();
  coordinator_->AddComponent(ball, TransformationComponent{coordinates});
  coordinator_->AddComponent(ball, MotionComponent{1.0});
  coordinator_->AddComponent(ball,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             {0.2, 0.2}});
  coordinator_->AddComponent(ball, CollisionComponent{
      CollisionType::kDefault, 1, 1, {0.2, 0.2}
  });
  coordinator_->AddComponent(ball, SerializationComponent{EntityType::kBall});
}

void Spawner::CreateWall(const QVector2D& coordinates) {
  Entity wall = coordinator_->CreateEntity();
  coordinator_->AddComponent(wall, TransformationComponent{coordinates});
  coordinator_->AddComponent(wall, MotionComponent{1.0});
  coordinator_->AddComponent(wall,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             {3.2, 0.2}});
  coordinator_->AddComponent(wall, CollisionComponent{
      CollisionType::kDefault, 0, 1, {3.2, 0.2}
  });
  coordinator_->AddComponent(wall, SerializationComponent{EntityType::kWall});
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
      CollisionType::kPlayer, 1, 0, {0.2, 0.2}
  });
  return player;
}

void Spawner::CreateDoor(const QVector2D& coordinates) {
  Entity door = coordinator_->CreateEntity();
  coordinator_->AddComponent(door, TransformationComponent{coordinates});
  coordinator_->AddComponent(door, MotionComponent{1.0});
  coordinator_->AddComponent(door,
                             PixmapComponent{QPixmap(":/textures/player.png"),
                                             {3.2, 0.2}});
  coordinator_->AddComponent(door, CollisionComponent{
      CollisionType::kRoomChanging, 0, 1, {3.2, 0.2}
  });
  coordinator_->AddComponent(door, SerializationComponent{EntityType::kDoor});
  coordinator_->AddComponent(door, DoorComponent{1});
}

void Spawner::CreateEntity(EntityType type, const QVector2D& pos) {
  switch (type) {
    case EntityType::kPlayer : {
      CreatePlayer(pos);
      break;
    }
    case EntityType::kWall : {
      CreateWall(pos);
      break;
    }
    case EntityType::kBall : {
      CreateBall(pos);
      break;
    }
    case EntityType::kDoor : {
      CreateDoor(pos);
      break;
    }
    default: {
      // TODO(Khody31) : do something here
    }
  }
}
