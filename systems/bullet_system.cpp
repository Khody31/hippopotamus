#include "bullet_system.h"
#include "engine/coordinator.h"
#include "game_components/components.h"

void BulletSystem::Update(Coordinator* coordinator) {
  for (Entity entity : entities_) {
    auto& tr = coordinator->GetComponent<TransformationComponent>(entity);
    tr.pos += tr.velocity;
  }
}

void BulletSystem::SetPlayer(Entity player) {
  player_ = player;
}

Entity BulletSystem::GetPlayer() {
  return player_;
}

void BulletSystem::CreateBullet(const QVector2D& point,
                                Coordinator* coordinator) {
  Entity bullet = coordinator->CreateEntity();
  coordinator->AddComponent(bullet, BulletIdentifierComponent{});
  const QVector2D& player_pos =
      coordinator->GetComponent<TransformationComponent>(player_).pos;
  QVector2D velocity = point - player_pos;
  velocity *= 0.15f / velocity.length();
  coordinator->AddComponent(bullet, TransformationComponent{
    player_pos, velocity });
  coordinator->AddComponent(bullet, PixmapComponent{
      QPixmap(":/player.png"),
      {0.1, 0.1},
      {0, 0},
      {0, 0}
  });
}
