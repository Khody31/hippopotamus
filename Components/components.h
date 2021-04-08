#pragma once

#include <QVector2D>
#include <QPixmap>

struct PhysicsComponent {
  double mass_ = 0;
  double restitution_;
  QVector2D size_{0, 0};
  QVector2D velocity_{0, 0};
};

struct PixmapComponent {
  QPixmap pixmap_;
  QVector2D size_;
};

struct TransformationComponent {
  QVector2D pos_;
  QVector2D velocity_;
};