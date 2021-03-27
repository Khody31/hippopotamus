#ifndef MOUSE_LISTENER_H_
#define MOUSE_LISTENER_H_

#include <iostream>

#include "engine/system/abstract_mouse_listener.h"

class MouseListener : public AbstractMouseListener {
 private:
  void OnLeftClick(const QVector2D& pos) override {
    std::cerr << "Left click on (" << pos.x() << "; " << pos.y() << ");\n";
  }
};

#endif  // MOUSE_LISTENER_H_
