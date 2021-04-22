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

struct CollisionComponent {
  // inverted mass = 1 / mass
  float inverted_mass;
  float elasticity;
  QVector2D size;
  QVector2D upper_left;
  QVector2D lower_right;
  QVector2D velocity;
};

struct JoystickComponent {};

struct MotionComponent {
  float speed = 0;
  QVector2D direction;
};
