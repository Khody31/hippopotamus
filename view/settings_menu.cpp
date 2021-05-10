#include "settings_menu.h"
#include "constants.h"

SettingsMenu::SettingsMenu(AbstractController* controller, QWidget* parent) :
    CustomWidget(controller, parent),
    sound_button_(new MenuButton(tr("SOUND"), this, menu_constants::kSound)),
    main_menu_button_(new MenuButton(tr("TO MAIN MENU"),
                                     this,
                                     menu_constants::kToMainMenu)) {
  connect(sound_button_, &::QPushButton::clicked, this, [&] {
    // ToDo
  });

  connect(main_menu_button_, &::QPushButton::clicked, this, [&] {
    controller_->OpenMainMenu();
  });
}

void SettingsMenu::Resize(QSize size) {
  sound_button_->setGeometry(sound_button_->CalculateActualPos(size));
  main_menu_button_->setGeometry(main_menu_button_->CalculateActualPos(size));
}
