#include "settings_menu.h"

#include "view/buttons/constants.h"

SettingsMenu::SettingsMenu(AbstractController* controller, QWidget* parent) :
    CustomWidget(controller, parent),
    sound_button_(new MenuButton(tr("TURN OFF SOUND"), this, constants::kSound)),
    main_menu_button_(new MenuButton(tr("TO MAIN MENU"),
                                     this,
                                     constants::kToMainMenu)) {
  connect(sound_button_, &::QPushButton::clicked, this, [&] {
    controller_->ChangeSoundState();
  });

  connect(main_menu_button_, &::QPushButton::clicked, this, [&] {
    controller_->OpenMainMenu();
  });
}

void SettingsMenu::Resize(QSize size) {
  sound_button_->setGeometry(sound_button_->CalculateActualPos(size));
  main_menu_button_->setGeometry(main_menu_button_->CalculateActualPos(size));
}

void SettingsMenu::ChangeSoundLabel(bool is_enabled) {
  if(is_enabled) {
    sound_button_->setText(tr("TURN OFF SOUND"));
  } else {
    sound_button_->setText(tr("TURN ON SOUND"));
  }
}