#include "engine/gov/governor.h"
#include "engine/core/game_scene.h"
#include "engine.h"
#include "engine/core/game_timer.h"
#include "engine/gov/logic_governor.h"

void Engine::Init() {
  static bool initialized{false};
  if (initialized) {
    throw std::logic_error("Engine already initialized");
  }
  initialized = true;
  GameTimer::Init();
  static Governor transformation_governor(ComponentIDs::kTransformationID);
  static GameScene pixmap_governor;
  static LogicGovernor logic_governor;
}
