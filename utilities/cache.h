#pragma once

#include <unordered_map>
#include <QString>
#include "core/animation_pack.h"

class Cache {
 public:
  Cache();
  AnimationPack* GetAnimationPack(const QString& path);

 private:
  std::unordered_map<QString, AnimationPack> path_to_animation_pack_{};
};
