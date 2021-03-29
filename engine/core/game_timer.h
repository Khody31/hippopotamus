#ifndef GAME_TIMER_H_
#define GAME_TIMER_H_

#include <QTimer>

class GameTimer : public QObject {
 Q_OBJECT
 public:
  GameTimer(const GameTimer&) = delete;
  GameTimer& operator=(const GameTimer&) = delete;

  static void Init();

 private:
  GameTimer() = default;

  QTimer timer_;

 private slots:
  void OnTick();
};

#endif  // GAME_TIMER_H_
