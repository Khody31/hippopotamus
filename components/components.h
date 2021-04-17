#pragma once

#include <QVector2D>
#include <QPixmap>

struct TransformationComponent {
  QVector2D pos;
};

struct PixmapComponent {
  QPixmap pixmap;
  QVector2D size;
  QPoint upper_left;
  QPoint lower_right;
};

struct JoystickComponent {};

struct MovementComponent {
  float speed = 0;
  QVector2D direction;
};
