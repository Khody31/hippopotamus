#include "bullet_system.h"
#include "engine/coordinator.h"
#include "components/components.h"

void BulletSystem::CreateBulletFor(Entity entity, const QVector2D& game_coord) {
  Entity bullet = coordinator_->CreateEntity();
  const QVector2D& entity_pos =
      coordinator_->GetComponent<TransformationComponent>(entity).pos;
  QVector2D velocity = game_coord - entity_pos;
  coordinator_->AddComponent(bullet, TransformationComponent{entity_pos});
  coordinator_->AddComponent(bullet, MotionComponent{0.15f, velocity});
  coordinator_->AddComponent(bullet, PixmapComponent{
      QPixmap(":/player.png"),
      {0.1, 0.1}
  });
}

void BulletSystem::SetCoordinator(Coordinator* coordinator) {
  coordinator_ = coordinator;
}
