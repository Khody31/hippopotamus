#pragma once
#include <iostream>

#include "engine/system/abstract_mouse_listener.h"

class MouseListener : public AbstractMouseListener {
 private:
  void OnLeftClick(const QVector2D& pos) override {
    std::cerr << "Left click on (" << pos.x() << "; " << pos.y() << ");\n";
  }
};
