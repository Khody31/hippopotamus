#include "game_timer.h"
#include "game_scene.h"

GameTimer::GameTimer() {
  timer.start(constants::kGameTickTime / kNumberOfStages);
  connect(&timer, &QTimer::timeout, this, &GameTimer::OnTick);
}

void GameTimer::OnTick() {
  static int iteration{0};
  for (const auto& object : objects_[iteration++ % kNumberOfStages]) {
    object->OnTick();
  }
  GameScene::GetInstance().repaint();
}
void GameTimer::StartTracking(UpdatableOnTickInterface* ptr) {
  static int counter{0};
  objects_[counter++ % kNumberOfStages].insert(ptr);
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
