#include "collision_system.h"
#include "components/components.h"
#include "core/connector.h"
#include "core/helpers.h"

#include <algorithm>
#include <utility>
#include <QVector2D>

void CollisionSystem::UpdateCollisionComponents(Coordinator* coordinator) {
  // synchronize collision component's fields with other components
  for (auto entity : entities_) {
    auto& transform_comp =
        coordinator->GetComponent<TransformationComponent>(entity);
    auto& collision_comp =
        coordinator->GetComponent<CollisionComponent>(entity);
    auto& motion_comp =
        coordinator->GetComponent<MotionComponent>(entity);

    collision_comp.pos = transform_comp.pos;
    collision_comp.velocity = motion_comp.speed
        * motion_comp.direction.normalized();
  }
}

void CollisionSystem::UpdateOtherComponents(Coordinator* coordinator) {
  // synchronize other component's field with collision components
  for (auto entity : entities_) {
    auto& transform_comp =
        coordinator->GetComponent<TransformationComponent>(entity);
    auto& collision_comp =
        coordinator->GetComponent<CollisionComponent>(entity);
    auto& motion_comp =
        coordinator->GetComponent<MotionComponent>(entity);

    transform_comp.pos = collision_comp.pos;
    motion_comp.speed = collision_comp.velocity.length();
    motion_comp.direction = collision_comp.velocity.normalized();
  }
}

bool CollisionSystem::IsCollisionNeeded() {
  return keyboard_->IsKeyPressed(KeyAction::kAction);
}

void CollisionSystem::Update(Coordinator* coordinator) {
  UpdateCollisionComponents(coordinator);

  for (auto fst_entity : entities_) {
    for (auto scd_entity : entities_) {
      if (fst_entity == scd_entity) {
        continue;
      }

      helpers::Collision collision{
          &coordinator->GetComponent<CollisionComponent>(fst_entity),
          &coordinator->GetComponent<CollisionComponent>(scd_entity),
      };

      if (IsCollisionPresent(&collision)) {
        if (collision.fst_collider->type == CollisionType::kRoomChanging &&
            collision.scd_collider->type == CollisionType::kPlayer) {
          if (IsCollisionNeeded()) {
            connector_->ChangeRoom(
                coordinator->GetComponent<DoorComponent>(fst_entity));
            return;
          }
        }

        if (collision.fst_collider->inverted_mass != 0 ||
            collision.scd_collider->inverted_mass != 0) {
          ResolveCollision(&collision);
          PositionalCorrection(&collision);
        }
      }
    }
  }

  UpdateOtherComponents(coordinator);
}

CollisionSystem::CollisionSystem() : keyboard_(nullptr), connector_(nullptr) {}

void CollisionSystem::SetKeyboardInterface(const KeyboardInterface* ptr) {
  keyboard_ = ptr;
}

void CollisionSystem::SetConnector(Connector* ptr) {
  connector_ = ptr;
}

const std::unordered_set<Entity>& CollisionSystem::GetEntities() {
  return entities_;
}
