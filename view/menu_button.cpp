#include <utility>

#include "menu_button.h"

MenuButton::MenuButton(const QString& title,
                       QWidget* parent,
                       QRect relative_pos) :
    QPushButton(title, parent), relative_pos_(relative_pos) {}

QRect MenuButton::CalculateActualPos(QSize size) {
  return QRect(relative_pos_.x() * size.width() / 100,
               relative_pos_.y() * size.height() / 100,
               relative_pos_.width() * size.width() / 100,
               relative_pos_.height() * size.height() / 100);
}

