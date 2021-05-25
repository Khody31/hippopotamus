#pragma once

#include <unordered_map>
#include <QString>

#include "core/animation_pack.h"

class Cache {
 public:
  Cache();
  AnimationPack* GetAnimationPack(const QString& path);

 private:
  std::unordered_map<QString, std::unique_ptr<AnimationPack>> path_to_pack_;
};
