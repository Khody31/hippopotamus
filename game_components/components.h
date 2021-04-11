#pragma once

#include <QVector2D>
#include <QPixmap>

struct TransformationComponent {
  QVector2D pos_;
  QVector2D velocity_;
};

struct PixmapComponent {
  QPixmap pixmap_;
  QVector2D size_;
  QPoint game_ul_;
  QPoint game_lr_;
};