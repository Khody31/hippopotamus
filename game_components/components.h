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
  QPoint game_ul;
  QPoint game_lr;
};