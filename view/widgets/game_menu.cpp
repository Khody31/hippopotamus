#include "game_menu.h"

#include <QKeyEvent>

#include "view/buttons/constants.h"

GameMenu::GameMenu(AbstractController* controller,
                   QWidget* parent) :
    CustomWidget(controller, parent, ":/menu/screen-options.png"),
    resume_button_(new MenuButton(":/menu/button-resume-the-game-en.png",
                                  this,
                                  constants::kResumeButton)),
    sound_button_(new MenuButton(":/menu/button-sound-off-en.png",
                                 this,
                                 constants::kSoundButton)),
    to_main_menu_button_(new MenuButton(":/menu/button-main-menu-en.png",
                                        this,
                                        constants::kToMainMenuButton)) {
  connect(resume_button_, &::QPushButton::clicked, this, [&] {
    controller_->ContinueGame();
  });

  connect(sound_button_, &::QPushButton::clicked, this, [&] {
    controller_->ChangeSoundState();
  });

  connect(to_main_menu_button_, &::QPushButton::clicked, this, [&] {
    controller_->OpenMainMenu();
  });
}

void GameMenu::Resize(QSize size) {
  resume_button_->setGeometry(resume_button_->CalculateActualPos(size));
  sound_button_->setGeometry(sound_button_->CalculateActualPos(size));
  to_main_menu_button_->setGeometry(to_main_menu_button_->CalculateActualPos
      (size));
}

void GameMenu::keyPressEvent(QKeyEvent* event) {
  // ignore event for it to be propagated to parent widget (Game CustomWidget)
  if (event->key() == Qt::Key_Escape) {
    QWidget::keyPressEvent(event);
  }
  controller_->OnKeyPress(event);
}

void GameMenu::keyReleaseEvent(QKeyEvent* event) {
  controller_->OnKeyRelease(event);
}

void GameMenu::ChangeLanguage(Language language) {
  switch (language) {
    case Language::kEnglish : {
      resume_button_->ChangePixmap(":/menu/button-resume-the-game-en.png");
      sound_button_->ChangePixmap(":/menu/button-sound-off-en.png");
      to_main_menu_button_->ChangePixmap(":/menu/button-main-menu-en.png");
      break;
    }
    case Language::kRussian : {
      resume_button_->ChangePixmap(":/menu/button-resume-the-game-ru.png");
      sound_button_->ChangePixmap(":/menu/button-sound-off-ru.png");
      to_main_menu_button_->ChangePixmap(":/menu/button-main-menu-ru.png");
      break;
    }
    case Language::kBelarusian : {
      resume_button_->ChangePixmap(":/menu/button-resume-the-game-by.png");
      sound_button_->ChangePixmap(":/menu/button-sound-off-by.png");
      to_main_menu_button_->ChangePixmap(":/menu/button-main-menu-by.png");
      break;
    }
  }
}

void GameMenu::ChangeSoundLabel(bool is_enabled, Language language) {
  switch (language) {
    case Language::kEnglish : {
      if (is_enabled) {
        sound_button_->ChangePixmap(":/menu/button-sound-off-en.png");
      } else {
        sound_button_->ChangePixmap(":/menu/button-sound-on-en.png");
      }
      break;
    }
    case Language::kRussian : {
      if (is_enabled) {
        sound_button_->ChangePixmap(":/menu/button-sound-off-ru.png");
      } else {
        sound_button_->ChangePixmap(":/menu/button-sound-on-ru.png");
      }
      break;
    }
    case Language::kBelarusian : {
      if (is_enabled) {
        sound_button_->ChangePixmap(":/menu/button-sound-off-by.png");
      } else {
        sound_button_->ChangePixmap(":/menu/button-sound-on-by.png");
      }
      break;
    }
  }
}
