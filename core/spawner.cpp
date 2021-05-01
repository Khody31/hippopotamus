#include "spawner.h"
#include "engine/coordinator.h"
#include "components/components.h"

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

void Spawner::CreateBall() {
  Entity ball = coordinator_->CreateEntity();
  coordinator_->AddComponent(ball, TransformationComponent{{1, 0.2}});
  coordinator_->AddComponent(ball, MotionComponent{1.0});
  coordinator_->AddComponent(ball, PixmapComponent{QPixmap(":/player.png"),
                                                   {0.2, 0.2}});
  coordinator_->AddComponent(ball, CollisionComponent{
      1, 1, {0.2, 0.2}
  });
}

void Spawner::CreateWall() {
  Entity wall = coordinator_->CreateEntity();
  coordinator_->AddComponent(wall, TransformationComponent{{0, 0.9}});
  coordinator_->AddComponent(wall, MotionComponent{1.0});
  coordinator_->AddComponent(wall, PixmapComponent{QPixmap(":/player.png"),
                                                   {3.2, 0.2}});
  coordinator_->AddComponent(wall, CollisionComponent{
      0, 1, {3.2, 0.2}
  });
}
