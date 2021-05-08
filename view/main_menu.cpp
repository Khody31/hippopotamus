#include "main_menu.h"
#include "constants.h"

MainMenu::MainMenu(AbstractController* controller,
                   QWidget* parent) :
    CustomWidget(controller, parent),
    new_game_button_(new MenuButton(tr("NEW GAME"),
                                    this,
                                    menu_constants::kNewGameButton)),
    load_game_button_(new MenuButton(tr("LOAD GAME"),
                                     this,
                                     menu_constants::kLoadGameButton)),
    settings_button_(new MenuButton(tr("SETTINGS"),
                                    this,
                                    menu_constants::kSettingsButton)),
    close_button_(new MenuButton(tr("EXIT"),
                                 this,
                                 menu_constants::kExitButton)) {

  connect(new_game_button_, &::QPushButton::clicked, this, [&]() {
    controller_->StartNewGame();
  });

  connect(load_game_button_, &::QPushButton::clicked, this, [&]() {
    controller_->LoadGame();
  });

  connect(settings_button_, &::QPushButton::clicked, this, [&]() {
    controller_->OpenSettings();
  });

  connect(close_button_, &::QPushButton::clicked, this, [&]() {
    controller_->Close();
  });
}

void MainMenu::Resize(QSize size) {
  new_game_button_->setGeometry(new_game_button_->CalculateActualPos(size));
  load_game_button_->setGeometry(load_game_button_->CalculateActualPos(size));
  settings_button_->setGeometry(settings_button_->CalculateActualPos(size));
  close_button_->setGeometry(close_button_->CalculateActualPos(size));
}

