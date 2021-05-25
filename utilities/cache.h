#pragma once

#include <unordered_map>
#include <QString>

#include "core/animation_pack.h"

class Cache {
 public:
  Cache();
  AnimationPack* GetAnimationPack(const std::string& path);

 private:
  std::unordered_map<std::string, std::unique_ptr<AnimationPack>> path_to_pack_;
};
