#pragma once

#include <QPushButton>

class MenuButton : public QPushButton {
 public:
  MenuButton(const QString& title, QWidget* parent, QRect relative_pos);
  QRect CalculateActualPos(QSize size);

 private:
  // pos in abstract widget 100 * 100
  QRect relative_pos_;
};
