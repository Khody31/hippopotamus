#pragma once

#include "view/buttons/menu_button.h"
#include "custom_widget.h"

class GameMenu : public CustomWidget {
 public:
  GameMenu(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;

 private:
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

  MenuButton* resume_button_;
  MenuButton* sound_button_;
  MenuButton* to_main_menu_button_;
};
