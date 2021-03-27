#ifndef MOUSE_HANDLER_INTERFACE_H_
#define MOUSE_HANDLER_INTERFACE_H_

#include <QVector2D>

class AbstractMouseListener {
 private:
  friend class GameWidget;

  virtual void OnLeftClick(const QVector2D& pos) = 0;
  virtual void OnLeftRelease(const QVector2D& pos) {};
  virtual void OnRightClick(const QVector2D& pos) {};
  virtual void OnRightRelease(const QVector2D& pos) {};
};

#endif  // MOUSE_HANDLER_INTERFACE_H_
