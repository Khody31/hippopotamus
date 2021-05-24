#include "cache.h"

Cache::Cache() {
  std::vector<QString> paths {
      ":/animations/demo.json",
      ":/animations/necromancer.json"
  };

  for (const auto& path : paths) {
    path_to_animation_pack_.emplace(path, path);
  }
}

AnimationPack* Cache::GetAnimationPack(const QString& path) {
  return &path_to_animation_pack_.at(path);
}
