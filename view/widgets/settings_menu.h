#pragma once

#include "view/widgets/custom_widget.h"
#include "view/buttons/menu_button.h"

class SettingsMenu : public CustomWidget {
 public:
  SettingsMenu(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;
  void ChangeSoundLabel(bool is_enabled);

 private:
  MenuButton* sound_button_;
  MenuButton* main_menu_button_;
};
