#pragma once

#include "Engine/Core/game_scene.h"
#include <QVector2D>
#include "Engine/Misc/vector_2d.h"

class PixmapComponentInterface {
 public:
  [[nodiscard]] virtual const QPixmap& GetPixmap() const = 0;
  [[nodiscard]] virtual int GetLayer() const = 0;
  [[nodiscard]] virtual Vector2D GetPosition() const = 0;
  [[nodiscard]] virtual Vector2D GetSize() const = 0;
};
