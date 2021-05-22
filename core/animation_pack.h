#pragma once

#include <QPixmap>
#include <unordered_map>
#include <memory>
#include <vector>

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

  const std::unordered_map<QString, AnimationType> str_to_type =
      {{"idle", AnimationType::kIdle}, {"left", AnimationType::kLeft},
       {"right", AnimationType::kRight}, {"up", AnimationType::kUp},
       {"down", AnimationType::kDown}};
};
