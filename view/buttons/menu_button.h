#pragma once

#include <QPushButton>

class MenuButton : public QPushButton {
  Q_OBJECT
 public:
  MenuButton(const QString& path_to_pixmap, QWidget* parent, QRect
  relative_pos);
  QRect CalculateActualPos(QSize size);
  void ChangePixmap(const QString& path_to_pixmap);
 private:
  void paintEvent(QPaintEvent* event) override;
  // position in abstract widget 100 * 100
  QRect relative_pos_;
  QPixmap* pixmap_;
};
