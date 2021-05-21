#include "collision_system.h"

#include "utilities/collisions.h"
#include "core/connector.h"

#include <unordered_set>

CollisionSystem::CollisionSystem(Connector* connector,
                                 Coordinator* coordinator,
                                 Keyboard* keyboard) :
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

      utility::Collision collision{
          &coordinator_->GetComponent<CollisionComponent>(first),
          &coordinator_->GetComponent<CollisionComponent>(second)};

      if (!IsCollisionPresent(&collision)) {
        continue;
      }

      if (coordinator_->HasComponent<DoorComponent>(first) &&
          coordinator_->HasComponent<JoystickComponent>(second) &&
          keyboard_->IsKeyPressed(KeyAction::kAction)) {
        connector_->ChangeRoom(
            coordinator_->GetComponent<DoorComponent>(first));
        return;
      }

      if (coordinator_->HasComponent<BulletComponent>(second)) {
        continue;
      }
      if (coordinator_->HasComponent<BulletComponent>(first)) {
        if (coordinator_->HasComponent<IntelligenceComponent>(second)) {
          float damage =
              coordinator_->GetComponent<DamageComponent>(first).value;
          coordinator_->
              GetComponent<HealthComponent>(second).value -= damage;
        }

        if (!coordinator_->HasComponent<JoystickComponent>(second)) {
          to_destroy.insert(first);
        }
        continue;
      }

      if (collision.first->inverted_mass != 0 ||
          collision.second->inverted_mass != 0) {
        ResolveCollision(&collision);
        PositionalCorrection(&collision);
      }
    }
  }

  for (auto entity : to_destroy) {
    coordinator_->DestroyEntity(entity);
  }

  UpdateOtherComponents();
}

const std::unordered_set<Entity>& CollisionSystem::GetEntities() {
  return entities_;
}
