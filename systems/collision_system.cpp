#include "collision_system.h"
#include "core/connector.h"
#include "core/helpers.h"

#include <unordered_set>

#include <QVector2D>

CollisionSystem::CollisionSystem(Connector* connector,
                                 Coordinator* coordinator,
                                 KeyboardInterface* keyboard) :
    connector_(connector), coordinator_(coordinator), keyboard_(keyboard) {}

void CollisionSystem::UpdateCollisionComponents() {
  // synchronize collision component's fields with other components
  for (auto entity : entities_) {
    auto& transform =
        coordinator_->GetComponent<TransformationComponent>(entity);
    auto& collision = coordinator_->GetComponent<CollisionComponent>(entity);
    auto& motion = coordinator_->GetComponent<MotionComponent>(entity);

    collision.pos = transform.pos;
    collision.velocity = motion.speed * motion.direction.normalized();
  }
}

void CollisionSystem::UpdateOtherComponents() {
  // synchronize other component's field with collision components
  for (auto entity : entities_) {
    auto& transform =
        coordinator_->GetComponent<TransformationComponent>(entity);
    auto& collision = coordinator_->GetComponent<CollisionComponent>(entity);
    auto& motion = coordinator_->GetComponent<MotionComponent>(entity);

    transform.pos = collision.pos;
    motion.speed = collision.velocity.length();
    motion.direction = collision.velocity.normalized();
  }
}

void CollisionSystem::Update() {
  UpdateCollisionComponents();

  std::unordered_set<Entity> to_destroy;
  for (auto first : entities_) {
    for (auto second : entities_) {
      if (first == second) {
        continue;
      }

      helpers::Collision collision{
          &coordinator_->GetComponent<CollisionComponent>(first),
          &coordinator_->GetComponent<CollisionComponent>(second)};

      if (!helpers::IsCollisionPresent(&collision)) {
        continue;
      }

      if (collision.first->type == CollisionType::kRoomChanging &&
          collision.second->type == CollisionType::kPlayer &&
          keyboard_->IsKeyPressed(KeyAction::kAction)) {
        connector_->
            ChangeRoom(coordinator_->GetComponent<DoorComponent>(first));
        return;
      }

      if (collision.second->type == CollisionType::kBullet) {
        continue;
      }
      if (collision.first->type == CollisionType::kBullet) {
        if (collision.second->type == CollisionType::kEnemy) {
          float damage =
              coordinator_->GetComponent<DamageComponent>(first).damage;
          coordinator_->
              GetComponent<HealthComponent>(second).health -= damage;
        }

        if (collision.second->type != CollisionType::kPlayer) {
          to_destroy.insert(first);
        }
        continue;
      }

      if (collision.first->inverted_mass != 0 ||
          collision.second->inverted_mass != 0) {
        helpers::ResolveCollision(&collision);
        helpers::PositionalCorrection(&collision);
      }
    }
  }

  for (auto entity : to_destroy) {
    coordinator_->DestroyEntity(entity);
  }

  UpdateOtherComponents();
}
