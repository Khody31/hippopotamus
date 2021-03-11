#pragma once

#include <QGraphicsPixmapItem>

#include "vector2d.h"
class GameObject : public QGraphicsPixmapItem {
  Q_OBJECT
 public:
 protected:
  Vector2D coordinates_;
};
