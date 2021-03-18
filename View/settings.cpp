#include "settings.h"

SettingsWidget::SettingsWidget(QWidget *parent,
                               AbstractController *controller) :
    QWidget(parent) {
  controller_ = controller;
  CreateButtons();
  LayoutPart();
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
  sound_ = new MenuButton(tr("SOUND"), this);
  to_main_menu_ = new MenuButton(tr("TO MAIN MENU"), this);
}

void SettingsWidget::ConnectButtons() {
  connect(sound_, &::QPushButton::clicked, this,
          &::SettingsWidget::SoundButtonPressEvent);
  connect(to_main_menu_, &::QPushButton::clicked, this,
          &::SettingsWidget::ToMainMenuButtonPressEvent);
}
void SettingsWidget::LayoutPart() {
  layout_ = new QVBoxLayout(this);
  layout_->addWidget(sound_);
  layout_->addWidget(to_main_menu_);
  setLayout(layout_);
}
