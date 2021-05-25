#pragma once

#include <QPixmap>
#include <unordered_map>
#include <memory>
#include <vector>

namespace AnimationType {
enum TypeID {
  kIdle,
  kLeft,
  kRight,
  kUp,
  kDown,
  kSpecial,

  kEnumSize
};
}  // namespace AnimationType

class AnimationPack {
 public:
  explicit AnimationPack(const std::string& path_to_json);
  const QPixmap* GetFrame(AnimationType::TypeID type,
                          uint64_t elapsed_time) const;
  uint64_t GetAnimationDuration(AnimationType::TypeID) const;

 private:
  std::array<std::vector<std::unique_ptr<QPixmap>>, AnimationType::kEnumSize>
      animations_;
  uint64_t frame_duration_;

  const std::unordered_map<std::string, AnimationType::TypeID> str_to_type =
      {{"idle", AnimationType::kIdle}, {"left", AnimationType::kLeft},
       {"right", AnimationType::kRight}, {"up", AnimationType::kUp},
       {"down", AnimationType::kDown}, {"special", AnimationType::kSpecial}};
};
