#pragma once

#include "custom_widget.h"
#include "view/buttons/menu_button.h"

class SettingsMenu : public CustomWidget {
 public:
  SettingsMenu(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;

 private:
  MenuButton* sound_button_;
  MenuButton* main_menu_button_;
};
