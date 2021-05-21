#pragma once

#include <QPixmap>
#include <unordered_map>

enum class AnimationType {
  kIdle,
  kLeft,
  kRight,
  kUp,
  kDown
};

class AnimationPack {
 public:
  explicit AnimationPack(const QString& path_to_json);
  const QPixmap* GetFrame(AnimationType type,
                          uint64_t elapsed_time) const;

 private:
  std::unordered_map<AnimationType, std::vector<std::unique_ptr<QPixmap>>>
      animations_;
  uint64_t frame_duration_;
};
