#include "animation_pack.h"

const QPixmap* AnimationPack::GetFrame(const QString& animation_name,
                                       uint64_t elapsed_time) {
  const auto& animation = animations_[animation_name];
  return animation.at((elapsed_time / frame_duration_) % animation.size()).get();
}

AnimationPack::AnimationPack(const QString& path_to_json) {

}
