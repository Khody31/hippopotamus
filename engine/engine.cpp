#include <engine/gov/governor.h>
#include <engine/core/game_scene.h>
#include "engine.h"
#include "engine/core/game_timer.h"

void Engine::Init() {
  static bool initialized{false};
  if (initialized) {
    throw std::logic_error("Engine already initialized");
  }
  GameTimer::Init();
  static Governor transformation_governor(ComponentIDs::kTransformationID);
  static GameScene pixmap_governor;
}
