#pragma once

#include <QVector2D>
#include <QPixmap>

struct TransformationComponent {
  QVector2D pos;
  QVector2D velocity;
};

struct PixmapComponent {
  QPixmap pixmap;
  QVector2D size;
  QPoint upper_left;
  QPoint lower_right;
};

struct BulletIdentifierComponent {

};
