#pragma once

#include <QVector2D>

#include "engine/components/enums/scene_layer_ids.h"

class PixmapComponentInterface {
 public:
  virtual void Update() = 0;

  [[nodiscard]] virtual const QPixmap& GetPixmap() const = 0;
  [[nodiscard]] virtual int GetLayer() const = 0;
  [[nodiscard]] virtual const QVector2D& GetPosition() const = 0;
  [[nodiscard]] virtual const QVector2D& GetSize() const = 0;
  virtual void SetLayer(SceneLayerID layer) = 0;
  };
