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
    if (animation.on_special_animation) {
      HandleSpecialAnimation(entity);
      continue;
    }
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
  const auto& motion =
      coordinator_->GetComponent<MotionComponent>(entity);
  constexpr float cos_60 = 0.5;
  AnimationType::TypeID desired_animation = AnimationType::kIdle;
  if (!motion.direction.isNull()) {
    desired_animation = AnimationType::kMoving;
  }
  SetAnimation(entity, desired_animation);
}

void AnimationSystem::HandleStaticAnimation(Entity entity) {
  SetAnimation(entity, AnimationType::kIdle);
}

void AnimationSystem::HandleSpecialAnimation(Entity entity) {
  auto& animation =
      coordinator_->GetComponent<AnimationComponent>(entity);
  if (animation.last_switch_timestamp == 0) {
    animation.last_switch_timestamp = timestamp_;
  }
  SetAnimation(entity, AnimationType::kSpecial);
  uint64_t special_animation_length =
      animation.animations->GetAnimationDuration(AnimationType::kSpecial);
  if (animation.last_switch_timestamp + special_animation_length
      <= timestamp_) {
    animation.on_special_animation = false;
  }
}

void AnimationSystem::SetAnimation(Entity entity,
                                   AnimationType::TypeID desired_animation) {
  auto& animation =
      coordinator_->GetComponent<AnimationComponent>(entity);
  auto& pixmap =
      coordinator_->GetComponent<PixmapComponent>(entity);

  if (animation.current_animation != desired_animation) {
    animation.current_animation = desired_animation;
    animation.last_switch_timestamp = timestamp_;
  }
  uint64_t delta = timestamp_ - animation.last_switch_timestamp;
  pixmap.pixmap = animation.animations->GetFrame(desired_animation, delta);
}
