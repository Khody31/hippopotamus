#pragma once

#include "view/widgets/custom_widget.h"
#include "view/buttons/menu_button.h"

class SettingsMenu : public CustomWidget {
 public:
  SettingsMenu(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;
  void ChangeSoundLabel(bool is_enabled, Language language);
  void ChangeLanguage(Language language) override;

 private:
  MenuButton* sound_button_;
  MenuButton* main_menu_button_;
  MenuButton* english_;
  MenuButton* russian_;
  MenuButton* belarussian_;
};
