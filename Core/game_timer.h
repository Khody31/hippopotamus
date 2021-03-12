#pragma once

#include <set>
#include <QTimer>

#include "Miscellaneous/singleton.h"
#include "Miscellaneous/constants.h"

class UpdatableOnTickInterface {
 public:
  virtual void OnTick() = 0;
};

class GameTimer : public Singleton, public QObject {
 Q_OBJECT
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
  QTimer timer;
};
