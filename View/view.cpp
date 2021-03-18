#include "view.h"

View::View(AbstractController *controller) : controller_(controller) {
 game_ = new GameWidget(this, controller);
 game_menu_ = new GameMenuWidget(this, controller);
 main_menu_ = new MainMenuWidget(this, controller);
 settings_ = new SettingsWidget(this, controller);
 switcher_ = new QStackedWidget(this);
 switcher_->addWidget(main_menu_);
 switcher_->addWidget(settings_);
 switcher_->addWidget(game_);
 switcher_->addWidget(game_menu_);
 SwitchToMainMenu();
 setMinimumSize(960, 540);
}

void View::SwitchToGame() {
 switcher_->setCurrentWidget(game_);
}

void View::SwitchToGameMenu() {
 switcher_->setCurrentWidget(game_menu_);
}

void View::SwitchToMainMenu() {
 switcher_->setCurrentWidget(main_menu_);
}

void View::SwitchToSettings() {
  switcher_->setCurrentWidget(settings_);
}

void View::resizeEvent(QResizeEvent *) {
  // TODO
}
