#include "settings.h"

SettingsWidget::SettingsWidget(QWidget *parent,
                               AbstractController *controller) :
    QWidget(parent) {
  controller_ = controller;
  CreateButtons();
  ConnectButtons();
}


void SettingsWidget::SoundButtonPressEvent() {
  // TODO
}

void SettingsWidget::ToMainMenuButtonPressEvent() {
  controller_->OpenMainMenu();
}

void SettingsWidget::ContinueButtonPressEvent() {
  controller_->ContinueGame();
}

void SettingsWidget::CreateButtons() {
  sound_ = new MenuButton(tr("SOUND"), this, QRect(35, 20, 30, 10));
  to_main_menu_ = new MenuButton(tr("TO MAIN MENU"), this, QRect(35, 35, 30,
                                                                 10));
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
