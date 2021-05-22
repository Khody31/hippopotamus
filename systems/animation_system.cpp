#include "core/constants.h"
#include "components/components.h"
#include "animation_system.h"
#include "engine/coordinator.h"

AnimationSystem::AnimationSystem(Coordinator* coordinator)
    : coordinator_(coordinator), timestamp_(0) {}

void AnimationSystem::Update() {
  timestamp_ += constants::kTickTime;
  for (Entity entity : entities_) {
    const auto& animation =
        coordinator_->GetComponent<AnimationComponent>(entity);
    switch (animation.type) {
      case AnimationPackType::kStatic: {
        HandleStaticAnimation(entity);
        break;
      }
      case AnimationPackType::kMoving: {
        HandleMovingAnimation(entity);
        break;
      }
    }
  }
}

void AnimationSystem::HandleMovingAnimation(Entity entity) {
  auto& animation =
      coordinator_->GetComponent<AnimationComponent>(entity);
  auto& pixmap =
      coordinator_->GetComponent<PixmapComponent>(entity);
  const auto& motion =
      coordinator_->GetComponent<MotionComponent>(entity);
  constexpr float cos_60 = 0.5;
  AnimationType desired_animation = AnimationType::kIdle;
  if (!motion.direction.isNull()) {
    auto direction = motion.direction.normalized();
    if (direction.x() >= cos_60) {
      desired_animation = AnimationType::kRight;
    } else if (direction.x() <= -cos_60) {
      desired_animation = AnimationType::kLeft;
    } else if (direction.y() >= 0) {
      desired_animation = AnimationType::kUp;
    } else {
      desired_animation = AnimationType::kDown;
    }
  }

  if (animation.current_animation != desired_animation) {
    animation.current_animation = desired_animation;
    animation.last_switch_timestamp = timestamp_;
  }
  uint64_t delta = timestamp_ - animation.last_switch_timestamp;
  pixmap.pixmap = animation.animations->GetFrame(desired_animation, delta);
}

void AnimationSystem::HandleStaticAnimation(Entity entity) {
  const auto& animation =
      coordinator_->GetComponent<AnimationComponent>(entity);
  auto& pixmap =
      coordinator_->GetComponent<PixmapComponent>(entity);
  uint64_t delta = timestamp_ - animation.last_switch_timestamp;
  pixmap.pixmap = animation.animations->GetFrame(AnimationType::kIdle, delta);
}
