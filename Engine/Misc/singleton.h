#pragma once

#include <QObject>

class QObjectSingleton : public QObject {
  Q_OBJECT
 public:
  QObjectSingleton(QObjectSingleton const&) = delete;
  void operator=(QObjectSingleton const&) = delete;

 protected:
  QObjectSingleton() = default;
};