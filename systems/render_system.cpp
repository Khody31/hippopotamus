#include "render_system.h"
#include "core/game_scene.h"

void RenderSystem::Update(GameScene* scene) {
  scene->repaint();
}

const std::unordered_set<Entity>& RenderSystem::GetEntities() {
  return entities_;
}
