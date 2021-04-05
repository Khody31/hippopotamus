#pragma  once

#include <QVector2D>
#include <QPixmap>

#include "component.h"

class PixmapComponent : public Component {
 public:
  PixmapComponent(QVector2D size, const QString& path);

  [[nodiscard]] const QVector2D& GetSize() const { return size_; }
  [[nodiscard]] const QPixmap& GetPixmap() const { return pixmap_; }

 private:
  QPixmap pixmap_;
  QVector2D size_;
};
