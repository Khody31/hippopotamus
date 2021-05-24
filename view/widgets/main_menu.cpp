#include "main_menu.h"

#include "view/buttons/constants.h"

MainMenu::MainMenu(AbstractController* controller,
                   QWidget* parent) :
    CustomWidget(controller, parent),
    new_game_button_(new MenuButton(tr("NEW GAME"),
                                    this,
                                    constants::kNewGameButton)),
    load_game_button_(new MenuButton(tr("LOAD GAME"),
                                     this,
                                     constants::kLoadGameButton)),
    settings_button_(new MenuButton(tr("SETTINGS"),
                                    this,
                                    constants::kSettingsButton)),
    close_button_(new MenuButton(tr("EXIT"),
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
      new_game_button_->setText(tr("NEW GAME"));
      load_game_button_->setText(tr("LOAD GAME"));
      settings_button_->setText(tr("SETTINGS"));
      close_button_->setText(tr("EXIT"));
      break;
    }
    case Language::kRussian : {
      new_game_button_->setText(tr("НОВАЯ ИГРА"));
      load_game_button_->setText(tr("ЗАГРУЗИТЬ ИГРУ"));
      settings_button_->setText(tr("НАСТРОЙКИ"));
      close_button_->setText(tr("ВЫХОД"));
      break;
    }
    case Language::kBelarusian : {
      new_game_button_->setText(tr("НОВАЯ ГУЛЬНЯ"));
      load_game_button_->setText(tr("ПРАЦЯГНУЦЬ ГУЛЬНЮ"));
      settings_button_->setText(tr("НАЛАДКІ"));
      close_button_->setText(tr("ВЫХАД"));
      break;
    }
  }
}

