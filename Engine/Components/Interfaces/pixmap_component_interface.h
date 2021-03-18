#pragma once

#include <QVector2D>
#include "Engine/Misc/vector_2d.h"
#include "Engine/Components/Enums/scene_layer_ids.h"

class PixmapComponentInterface {
 public:
  [[nodiscard]] virtual const QPixmap& GetPixmap() const = 0;
  [[nodiscard]] virtual int GetLayer() const = 0;
  [[nodiscard]] virtual Vector2D GetPosition() const = 0;
  [[nodiscard]] virtual Vector2D GetSize() const = 0;
  virtual void SetLayer(SceneLayerID layer) = 0;
  };
