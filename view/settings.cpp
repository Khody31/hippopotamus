#include "settings.h"
#include "constants.h"

SettingsWidget::SettingsWidget(QWidget* parent, AbstractController*
                                                                  controller) :
    QWidget(parent), controller_(controller) {
  CreateButtons();
  ConnectButtons();
}

void SettingsWidget::SoundButtonPressEvent() {
  // TODO(polchernikova): add sound button switching
}

void SettingsWidget::ToMainMenuButtonPressEvent() {
  controller_->OpenMainMenu();
}

void SettingsWidget::CreateButtons() {
  sound_ = new MenuButton(tr("SOUND"), this, menu_constants::sound);
  to_main_menu_ =
      new MenuButton(tr("TO MAIN MENU"), this, menu_constants::to_main_menu);
}

void SettingsWidget::ConnectButtons() {
  connect(sound_, &::QPushButton::clicked, this,
          &::SettingsWidget::SoundButtonPressEvent);
  connect(to_main_menu_, &::QPushButton::clicked, this,
          &::SettingsWidget::ToMainMenuButtonPressEvent);
}

void SettingsWidget::Resize(QSize size) {
  sound_->setGeometry(sound_->CalculateActualPos(size));
  to_main_menu_->setGeometry(to_main_menu_->CalculateActualPos(size));
}
