#ifndef HIPPOPOTAMUS_MENU_BUTTON_H
#define HIPPOPOTAMUS_MENU_BUTTON_H

#include <QPushButton>


class MenuButton : public QPushButton {
 public:
  MenuButton(const QString &title, QWidget *parent, QRect relative_pos,
             QString main_icon_pass = "", QString second_icon_pass = "");
  [[nodiscard]] QRect GetPos();
  [[nodiscard]] QRect CalculateActualPos(QSize size);
  void SwitchIcon();
 private:
  // pos in abstact widget 100 * 100
 QRect relative_pos_;
 QIcon* current_icon_ = nullptr;
  // for sound on/off and pause/play
 QIcon* hiden_icon_ = nullptr;
};


#endif //HIPPOPOTAMUS_MENU_BUTTON_H
