#pragma  once

#include <QTimer>

class GameTimer : public QObject {
 Q_OBJECT
 public:
  explicit GameTimer();
 private:
  QTimer timer_;

 private slots:
  void OnTick();
};
