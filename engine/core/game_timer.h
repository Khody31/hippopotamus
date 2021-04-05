#pragma  once

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
