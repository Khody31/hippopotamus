#include "main_menu.h"
#include "view/buttons/constants.h"

MainMenu::MainMenu(AbstractController* controller,
                   QWidget* parent) :
    CustomWidget(controller, parent, ":/menu/screen-options.png"),
    new_game_button_(new MenuButton(":/menu/button-new-game-en.png",
                                    this,
                                    constants::kNewGameButton)),
    load_game_button_(new MenuButton(":/menu/button-continue-en.png",
                                     this,
                                     constants::kLoadGameButton)),
    settings_button_(new MenuButton(":/menu/button-options-en.png",
                                    this,
                                    constants::kSettingsButton)),
    close_button_(new MenuButton(":/menu/button-exit-en.png",
                                 this,
                                 constants::kExitButton)) {
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

void MainMenu::ChangeLanguage(Language language) {
  switch (language) {
    case Language::kEnglish : {
      new_game_button_->ChangePixmap(":/menu/button-new-game-en.png");
      load_game_button_->ChangePixmap(":/menu/button-continue-en.png");
      settings_button_->ChangePixmap(":/menu/button-options-en.png");
      close_button_->ChangePixmap(":/menu/button-exit-en.png");
      break;
    }
    case Language::kRussian : {
      new_game_button_->ChangePixmap(":/menu/button-new-game-ru.png");
      load_game_button_->ChangePixmap(":/menu/button-continue-ru.png");
      settings_button_->ChangePixmap(":/menu/button-options-ru.png");
      close_button_->ChangePixmap(":/menu/button-exit-ru.png");
      break;
    }
    case Language::kBelarusian : {
      new_game_button_->ChangePixmap(":/menu/button-new-game-by.png");
      load_game_button_->ChangePixmap(":/menu/button-continue-by.png");
      settings_button_->ChangePixmap(":/menu/button-options-by.png");
      close_button_->ChangePixmap(":/menu/button-exit-by.png");
      break;
    }
  }
}
