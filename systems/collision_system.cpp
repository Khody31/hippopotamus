#include "collision_system.h"

#include "core/collisions.h"
#include "core/connector.h"

#include <unordered_set>

CollisionSystem::CollisionSystem(Connector* connector,
                                 Coordinator* coordinator,
                                 Keyboard* keyboard,
                                 Entity* player) :
    connector_(connector),
    coordinator_(coordinator),
    keyboard_(keyboard),
    player_(player) {}

void CollisionSystem::UpdateCollisionComponents() {
  // synchronize collision component's fields with other components
  for (auto entity : entities_) {
    auto& transform =
        coordinator_->GetComponent<TransformationComponent>(entity);
    auto& collision = coordinator_->GetComponent<CollisionComponent>(entity);
    auto& motion = coordinator_->GetComponent<MotionComponent>(entity);

    collision.position = transform.position;
    collision.velocity = motion.current_speed * motion.direction.normalized();
  }
}

void CollisionSystem::UpdateOtherComponents() {
  // synchronize other component's field with collision components
  for (auto entity : entities_) {
    auto& transform =
        coordinator_->GetComponent<TransformationComponent>(entity);
    auto& collision = coordinator_->GetComponent<CollisionComponent>(entity);
    auto& motion = coordinator_->GetComponent<MotionComponent>(entity);

    transform.position = collision.position;
    motion.current_speed = collision.velocity.length();
    motion.direction = collision.velocity.normalized();
  }
}

void CollisionSystem::Update() {
  UpdateCollisionComponents();

  std::unordered_set<Entity> to_destroy;
  for (Entity first : entities_) {
    for (Entity second : entities_) {
      if (first == second) {
        continue;
      }

      Collision collision{
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

      if (coordinator_->HasComponent<ArtifactComponent>(second)) {
        continue;
      }

      if (coordinator_->HasComponent<ArtifactComponent>(first)) {
        if (second != *player_) {
          continue;
        }
        connector_->GivePlayerBuff(
            coordinator_->GetComponent<ArtifactComponent>(first).buff_type);
        to_destroy.insert(first);
        continue;
      }

      if (first == *player_ &&
          coordinator_->HasComponent<IntelligenceComponent>(second)) {
        float damage =
            coordinator_->GetComponent<DamageComponent>(second).value;
        coordinator_->
            GetComponent<HealthComponent>(first).value -= damage;
      }

      if (coordinator_->HasComponent<BulletComponent>(second)) {
        continue;
      }
      if (coordinator_->HasComponent<BulletComponent>(first)) {
        if (second == *player_) {
          continue;
        }

        if (coordinator_->HasComponent<IntelligenceComponent>(second)) {
          float damage =
              coordinator_->GetComponent<DamageComponent>(first).value;
          coordinator_->
              GetComponent<HealthComponent>(second).value -= damage;
        }

        auto& first_bullet_comp =
            coordinator_->GetComponent<BulletComponent>(first);
        if (first_bullet_comp.type == BulletType::kSimple) {
          to_destroy.insert(first);
          continue;
        } else /*if (first_bullet_comp.type == kFireball)*/ {
          if (first_bullet_comp.num_of_wall_hits
              > BulletComponent::max_num_of_wall_hits) {
            to_destroy.insert(first);
          } else {
            first_bullet_comp.num_of_wall_hits++;
          }
        }
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
