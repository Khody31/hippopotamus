#pragma once

#include "view/widgets/custom_widget.h"
#include "view/buttons/menu_button.h"

class MainMenu : public CustomWidget {
 public:
  MainMenu(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;
  void ChangeLanguage(Language language) override;

 private:
  MenuButton* load_game_button_;
  MenuButton* new_game_button_;
  MenuButton* settings_button_;
  MenuButton* close_button_;
};
