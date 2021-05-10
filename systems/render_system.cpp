#include "render_system.h"
#include "core/scene.h"

RenderSystem::RenderSystem(Scene* scene) : scene_(scene) {
}

void RenderSystem::Update() {
  scene_->repaint();
}
