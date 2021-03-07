#pragma once

#include <QGraphicsPixmapItem>

struct Coordinates {
  double x = 0;
  double y = 0;
};

class GameObject : public QGraphicsPixmapItem {
  Q_OBJECT
 public:
 protected:
  Coordinates coordinates_;
};
