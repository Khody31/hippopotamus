#include "core/constants.h"
#include "animation_system.h"
#include "core/connector.h"
#include "engine/coordinator.h"

AnimationSystem::AnimationSystem(Connector* connector,
                                 Coordinator* coordinator)
    : connector_(connector), coordinator_(coordinator), current_time_(0) {}

void AnimationSystem::Update() {
  current_time_ += constants::kTickTime;
  for (Entity entity : entities_) {
    auto& motion_comp = coordinator_->GetComponent<MotionComponent>(entity);
    auto& animation_comp =
        coordinator_->GetComponent<AnimationComponent>(entity);
    auto& pixmap_comp = coordinator_->GetComponent<PixmapComponent>(entity);
    auto appropriate_animation = AnimationComponent::States::kIdle;
    if (!(motion_comp.direction == QVector2D{0.0, 0.0})) {
      motion_comp.direction.normalize();
      if (motion_comp.direction.x() >= 0.5) {
        appropriate_animation = AnimationComponent::States::kRight;
      } else if (motion_comp.direction.x() <= -0.5) {
        appropriate_animation = AnimationComponent::States::kLeft;
      } else if (motion_comp.direction.y() <= 0) {
        appropriate_animation = AnimationComponent::States::kDown;
      } else {
        appropriate_animation = AnimationComponent::States::kUp;
      }
    }
    if (appropriate_animation != animation_comp.current) {
      animation_comp.last_switch_timestamp = current_time_;
    }
    animation_comp.current = appropriate_animation;
    assert(animation_comp.animations[animation_comp.current]
               && "No animation provided");
    pixmap_comp.pixmap = animation_comp.animations[animation_comp.current]->GetFrame(
        current_time_ - animation_comp.last_switch_timestamp);
  }
}
