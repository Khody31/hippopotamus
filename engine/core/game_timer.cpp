#include "game_timer.h"
#include "engine/misc/constants.h"
#include "engine/gov/governors_handler.h"

void GameTimer::Init() {
  static bool initialized{false};
  if (initialized) {
    throw std::logic_error("Timer already initialized");
  }
  initialized = true;

  static GameTimer instance;
  instance.timer_.start(constants::kTickTime);

  connect(&instance.timer_, SIGNAL(timeout()), &instance, SLOT(OnTick()));
}

void GameTimer::OnTick() {
  GovernorsHandler::Get().OnTick();
}
