#include "game_timer.h"

#include "engine/core/game_scene.h"

GameTimer::GameTimer() {
  timer.start(constants::kGameTickTime / kRendersPerTick);
  connect(&timer, &QTimer::timeout, this, &GameTimer::OnTick);
}

void GameTimer::OnTick() {
  static uint64_t iteration{0};
  ++iteration;
  for (const auto& object : objects_[iteration % kRendersPerTick]) {
    object->OnTick();
  }
  GameScene::GetInstance().repaint();
}

void GameTimer::StartTracking(UpdatableOnTickInterface* ptr) {
  static uint64_t counter{0};
  objects_[counter++ % kRendersPerTick].insert(ptr);
}

void GameTimer::StopTracking(UpdatableOnTickInterface* ptr) {
  for (auto& objects_set : objects_) {
    objects_set.erase(ptr);
  }
}

GameTimer& GameTimer::GetInstance() {
  static GameTimer instance;
  return instance;
}
