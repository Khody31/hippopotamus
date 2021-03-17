#pragma once

#include <QObject>
#include "Engine/Components/pixmap_component.h"
#include "Engine/Components/transformation_component.h"

class GameObject : public QObject {
 public:
  [[nodiscard]] TransformationComponent* GetTransformationComponent() const;
  [[nodiscard]] PixmapComponent* GetPixmapComponent() const;

 private:
  TransformationComponent* transformation_component_{nullptr};
  PixmapComponent* pixmap_component_{nullptr};
};
