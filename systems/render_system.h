#pragma once

#include "engine/coordinator.h"
#include "core/scene.h"

class RenderSystem : public System {
 public:
  explicit RenderSystem(Scene* scene);
  void Update();

 private:
  Scene* scene_;
};
