#include <vector>

#include "cache.h"

Cache::Cache() {
  std::vector<std::string> paths {
      ":/animations/necromancer.json",
      ":/animations/player.json",
      ":/animations/door.json",
      ":/animations/buff-hp.json",
      ":/animations/buff-up.json",
      ":/animations/skeleton.json",
      ":/animations/wasp.json"
  };

  for (const auto& path : paths) {
    path_to_pack_.insert({path, std::make_unique<AnimationPack>(path)});
  }
}

AnimationPack* Cache::GetAnimationPack(const std::string& path) {
  if (path_to_pack_.find(path) == path_to_pack_.end()) {
    path_to_pack_.insert({path, std::make_unique<AnimationPack>(path)});
  }
  return path_to_pack_.at(path).get();
}
