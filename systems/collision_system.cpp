#include <algorithm>
#include <utility>

#include "collision_system.h"
#include "core/connector.h"

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

  for (auto first : entities_) {
    for (auto second : entities_) {
      if (first == second) {
        continue;
      }

      Collision collision
          {&coordinator_->GetComponent<CollisionComponent>(first),
           &coordinator_->GetComponent<CollisionComponent>(second)};

      if (!IsCollisionPresent(&collision)) {
        continue;
      }

      if (collision.first->type == CollisionType::kRoomChanging &&
          collision.second->type == CollisionType::kPlayer &&
          keyboard_->IsKeyPressed(KeyAction::kAction)) {
        connector_->
            ChangeRoom(coordinator_->GetComponent<DoorComponent>(first));
        return;
      }

      if (collision.first->inverted_mass != 0 ||
          collision.second->inverted_mass != 0) {
        ResolveCollision(&collision);
        PositionalCorrection(&collision);
      }
    }
  }

  UpdateOtherComponents();
}

std::pair<float, float> CalculateOverlaps(Collision* collision) {
  CollisionComponent* first = collision->first;
  CollisionComponent* second = collision->second;

  std::array<float, 2> result{};
  for (int i = 0; i < 2; ++i) {
    float first_right = (first->pos + first->size / 2)[i];
    float second_right = (second->pos + second->size / 2)[i];
    float first_left = (first->pos - first->size / 2)[i];
    float second_left = (second->pos - second->size / 2)[i];
    result[i] =
        std::min(first_right, second_right) - std::max(first_left, second_left);
  }
  return {result[0], result[1]};
}

bool IsCollisionPresent(Collision* collision) {
  auto[x_overlap, y_overlap] = CalculateOverlaps(collision);
  QVector2D first_to_second = collision->second->pos - collision->first->pos;

  if (!(x_overlap > 0 && y_overlap > 0)) {
    return false;
  }

  if (x_overlap < y_overlap) {
    if (first_to_second.x() < 0) {
      collision->normal = QVector2D(-1, 0);
    } else {
      collision->normal = QVector2D(1, 0);
    }
    collision->penetration = x_overlap;
    return true;
  }

  if (first_to_second.y() < 0) {
    collision->normal = QVector2D(0, -1);
  } else {
    collision->normal = QVector2D(0, 1);
  }
  collision->penetration = y_overlap;
  return true;
}

void ResolveCollision(Collision* collision) {
  CollisionComponent* first = collision->first;
  CollisionComponent* second = collision->second;
  QVector2D normal = collision->normal;

  QVector2D relative_velocity = second->velocity - first->velocity;
  float velocity_along_normal = relative_velocity.x() * normal.x() +
      relative_velocity.y() * normal.y();

  // we don't solve the collision if it will be solved itself
  if (velocity_along_normal > 0) {
    return;
  }

  float elasticity = std::min(first->elasticity, second->elasticity);
  float impulse_module = -(1 + elasticity) * velocity_along_normal;
  impulse_module /= first->inverted_mass + second->inverted_mass;

  QVector2D impulse = impulse_module * normal;
  first->velocity -= first->inverted_mass * impulse;
  second->velocity += second->inverted_mass * impulse;
}

// needed to solve problem with drowning colliders
void PositionalCorrection(Collision* collision) {
  float percent = 0.2;
  float slop = 0.01;

  CollisionComponent* first = collision->first;
  CollisionComponent* second = collision->second;

  QVector2D correction = std::max(collision->penetration - slop, 0.0f)
      / (first->inverted_mass + second->inverted_mass) * percent
      * collision->normal;

  first->pos -= first->inverted_mass * correction;
  second->pos += second->inverted_mass * correction;
}
