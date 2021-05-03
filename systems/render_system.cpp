#include <unordered_set>

#include "render_system.h"
#include "core/game_scene.h"

void RenderSystem::Update(GameScene* scene) {
  scene->repaint();
}

const std::set<Entity>& RenderSystem::GetEntities() {
  return entities_;
}
