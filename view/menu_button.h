#pragma once

#include <QPushButton>

class MenuButton : public QPushButton {
 public:
  MenuButton(const QString& title, QWidget* parent, QRect relative_pos,
             const QString& main_icon_pass = "", const QString&
  second_icon_pass = "");
  ~MenuButton() override;
  [[nodiscard]] QRect GetPos();
  [[nodiscard]] QRect CalculateActualPos(QSize size);
  void SwitchIcon();

 private:
  // pos in abstract widget 100 * 100
  QRect relative_pos_;
  QIcon* current_icon_ = nullptr;
  // for sound on/off and pause/play
  QIcon* hidden_icon_ = nullptr;
};
