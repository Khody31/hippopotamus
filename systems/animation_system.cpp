#include <iostream>
#include "core/constants.h"
#include "animation_system.h"
#include "core/connector.h"
#include "engine/coordinator.h"

AnimationSystem::AnimationSystem(Coordinator* coordinator)
    : coordinator_(coordinator), current_time_(0) {}

void AnimationSystem::Update() {
  current_time_ += constants::kTickTime;
  for (Entity entity : entities_) {
    auto& animation_comp =
        coordinator_->GetComponent<AnimationComponent>(entity);
    switch(animation_comp.type) {
      case AnimationComponent::kStatic: {
        HandleStaticAnimation(entity);
        break;
      }
      case AnimationComponent::kMoving: {
        HandleMovingAnimation(entity);
        break;
      }
    }
  }
}
void AnimationSystem::HandleMovingAnimation(Entity entity) {
  auto& motion_comp = coordinator_->GetComponent<MotionComponent>(entity);
  auto& animation_comp = coordinator_->GetComponent<AnimationComponent>(entity);
  auto& pixmap_comp = coordinator_->GetComponent<PixmapComponent>(entity);
  auto appropriate_animation = AnimationComponent::State::kIdle;
  if (!(motion_comp.direction == QVector2D{0.0, 0.0})) {
    motion_comp.direction.normalize();
    if (motion_comp.direction.x() >= 0.5) {
      appropriate_animation = AnimationComponent::State::kRight;
    } else if (motion_comp.direction.x() <= -0.5) {
      appropriate_animation = AnimationComponent::State::kLeft;
    } else if (motion_comp.direction.y() <= 0) {
      appropriate_animation = AnimationComponent::State::kDown;
    } else {
      appropriate_animation = AnimationComponent::State::kUp;
    }
  }
  if (appropriate_animation != animation_comp.current) {
    animation_comp.last_switch_timestamp = current_time_;
  }
  animation_comp.current = appropriate_animation;
  assert(animation_comp.animations[animation_comp.current]
             && "No animation provided");
  pixmap_comp.pixmap =
      animation_comp.animations[animation_comp.current]->GetFrame(
          current_time_ - animation_comp.last_switch_timestamp);
}
void AnimationSystem::HandleStaticAnimation(Entity entity) {
  auto& animation_comp = coordinator_->GetComponent<AnimationComponent>(entity);
  auto& pixmap_comp = coordinator_->GetComponent<PixmapComponent>(entity);
  pixmap_comp.pixmap = animation_comp.animations[0]->GetFrame(current_time_);
}
