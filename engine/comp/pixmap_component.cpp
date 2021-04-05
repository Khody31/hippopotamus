#include <iostream>
#include "pixmap_component.h"

PixmapComponent::PixmapComponent(QVector2D size, const QString& path)
    : Component(ComponentIDs::kPixmapID),
      pixmap_(QPixmap(path)),
      size_(size) {
  if (pixmap_.isNull()) {
    std::cerr << "(PixmapComponent::PixmapComponent) Pixmap is NULL" << std::endl;
  }
}
