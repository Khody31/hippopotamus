#pragma once

#include <QPushButton>

class MenuButton : public QPushButton {
  Q_OBJECT
 public:
  MenuButton(const QString& title, QWidget* parent, QRect relative_pos);
  QRect CalculateActualPos(QSize size);

 private:
  // position in abstract widget 100 * 100
  QRect relative_pos_;
};
