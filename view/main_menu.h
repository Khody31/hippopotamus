#pragma once

#include "custom_widget.h"
#include "menu_button.h"

class MainMenu : public CustomWidget {
 public:
  MainMenu(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;

 private:
  MenuButton* load_game_button_;
  MenuButton* new_game_button_;
  MenuButton* settings_button_;
  MenuButton* close_button_;
};
