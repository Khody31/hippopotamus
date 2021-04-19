#include "menu_button.h"

MenuButton::MenuButton(const QString &title, QWidget *parent,
                       QRect relative_pos, QString main_icon_pass,
                       QString second_icon_pass) :
                       QPushButton(title, parent) {
  relative_pos_ = relative_pos;
  // current_icon_ = new QIcon(main_icon_pass);
  // hiden_icon_ = new QIcon(second_icon_pass);
  // setIcon(*current_icon_);
}

QRect MenuButton::GetPos() {
  return relative_pos_;
}

QRect MenuButton::CalculateActualPos(QSize size) {
  return QRect(relative_pos_.x() * size.width() / 100,
               relative_pos_.y() * size.height() / 100,
               relative_pos_.width() * size.width() / 100,
               relative_pos_.height() * size.height() / 100);
}

void MenuButton::SwitchIcon() {
 std::swap(current_icon_, hiden_icon_);
 setIcon(*current_icon_);
}
