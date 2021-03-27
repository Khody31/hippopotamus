#pragma once

#include <set>
#include <QTimer>

#include "Engine/Misc/singleton.h"
#include "Engine/Misc/constants.h"
#include "Engine/Components/Interfaces/updatable_on_tick_interface.h"

class GameTimer : public QObjectSingleton {
 public:
  static GameTimer& GetInstance();

 private:
  friend class UpdatableOnTick;

  static constexpr int kNumberOfStages{2};

  GameTimer();
  void OnTick();

  void StartTracking(UpdatableOnTickInterface* ptr);
  void StopTracking(UpdatableOnTickInterface* ptr);

  std::set<UpdatableOnTickInterface*> objects_[kNumberOfStages];
  GameScene* scene_;
  QTimer timer;
};
