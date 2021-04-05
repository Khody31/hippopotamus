#pragma  once

#include <QVector2D>

class AbstractMouseListener {
 private:
  friend class GameWidget;

  virtual void OnLeftClick(const QVector2D& pos) = 0;
  virtual void OnLeftRelease(const QVector2D& pos) {}
  virtual void OnRightClick(const QVector2D& pos) {}
  virtual void OnRightRelease(const QVector2D& pos) {}
};
