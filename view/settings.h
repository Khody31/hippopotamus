#ifndef HIPPOPOTAMUS_SETTINGS_H
#define HIPPOPOTAMUS_SETTINGS_H

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"
#include "abstract_controller.h"


class SettingsWidget: public QWidget {
 public:
  SettingsWidget(QWidget* parent, AbstractController* controller);
  void SoundButtonPressEvent();
  void ToMainMenuButtonPressEvent();
  void Resize(QSize size);
 private:
  MenuButton* sound_;
  MenuButton* to_main_menu_;
  AbstractController* controller_;
  void CreateButtons();
  void ConnectButtons();
};


#endif //HIPPOPOTAMUS_SETTINGS_H
