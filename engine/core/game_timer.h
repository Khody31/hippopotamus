#pragma once

#include <set>
#include <QTimer>

#include "engine/misc/singleton.h"
#include "engine/misc/constants.h"
#include "engine/components/interfaces/updatable_on_tick_interface.h"

class GameTimer : public QObjectSingleton {
 public:
  static GameTimer& GetInstance();

 private:
  friend class UpdatableOnTick;

  static constexpr int kRendersPerTick{2};

  GameTimer();
  void OnTick();

  void StartTracking(UpdatableOnTickInterface* ptr);
  void StopTracking(UpdatableOnTickInterface* ptr);

  std::array<std::set<UpdatableOnTickInterface*>, kRendersPerTick> objects_;
  QTimer timer;
};
