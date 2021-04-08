#include "game_timer.h"
#include "game_constants.h"

GameTimer::GameTimer() {
  timer_.start(game_constants::kTickTime);
  connect(&timer_, SIGNAL(timeout()), this, SLOT(OnTick()));
}

void GameTimer::OnTick() {

}
