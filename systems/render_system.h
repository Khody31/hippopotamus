#pragma once

#include "engine/coordinator.h"

class Scene;

class RenderSystem : public System {
 public:
  explicit RenderSystem(Scene* scene);
  void Update();

 private:
  Scene* scene_;
};
