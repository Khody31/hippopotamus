#include "view.h"

View::View(AbstractController* controller) :
    game_(new GameWidget(this, controller)),
    game_menu_(new GameMenuWidget(this, controller)),
    main_menu_(new MainMenuWidget(this, controller)),
    settings_(new SettingsWidget(this, controller)),
    switcher_(new QStackedWidget(this)) {
  AddWidgets();
  SwitchToMainMenu();
  resize(1600, 900);
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

void View::resizeEvent(QResizeEvent* event) {
  QSize new_size = size();
  switcher_->resize(new_size);
  game_->Resize(new_size);
  game_menu_->Resize(new_size);
  main_menu_->Resize(new_size);
  settings_->Resize(new_size);
}

void View::ContinueGame() {
  game_->Continue();
}

void View::PauseGame() {
  game_->Pause();
}

void View::StartGame() {
  game_->Start();
}

void View::StopGame() {
  game_->Stop();
}

void View::AddWidgets() {
  switcher_->addWidget(main_menu_);
  switcher_->addWidget(settings_);
  switcher_->addWidget(game_);
  switcher_->addWidget(game_menu_);
}
