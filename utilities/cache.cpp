#include <vector>

#include "cache.h"

Cache::Cache() {
  std::vector<QString> paths {
      ":/animations/demo.json",
      ":/animations/necromancer.json"
  };

  for (const auto& path : paths) {
    path_to_pack_.insert({path, std::make_unique<AnimationPack>(path)});
  }
}

AnimationPack* Cache::GetAnimationPack(const QString& path) {
  if (path_to_pack_.find(path) == path_to_pack_.end()) {
    path_to_pack_.insert({path, std::make_unique<AnimationPack>(path)});
  }
  return path_to_pack_.at(path).get();
}
