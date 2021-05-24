#include "game_menu.h"

#include <QKeyEvent>

#include "view/buttons/constants.h"

GameMenu::GameMenu(AbstractController* controller,
                   QWidget* parent) :
    CustomWidget(controller, parent),
    resume_button_(new MenuButton(tr("RESUME"),
                                  this,
                                  constants::kResumeButton)),
    sound_button_(new MenuButton(tr("TURN OFF SOUND"),
                                 this,
                                 constants::kSoundButton)),
    to_main_menu_button_(new MenuButton(tr("TO MAIN MENU"),
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
      resume_button_->setText(tr("RESUME"));
      sound_button_->setText(tr("TURN OFF SOUND"));
      to_main_menu_button_->setText(tr("TO MAIN MENU"));
          break;
    }
    case Language::kRussian : {
      resume_button_->setText(tr("ПРОДОЛЖИТЬ"));
      sound_button_->setText(tr("ВЫКЛЮЧИТЬ ЗВУК"));
      to_main_menu_button_->setText(tr("В ГЛАВНОЕ МЕНЮ"));
      break;
    }
    case Language::kBelarusian : {
      resume_button_->setText(tr("ПРАДОЎЖЫЦЬ"));
      sound_button_->setText(tr("ВЫКЛЮЧЫЦЬ ГУК"));
      to_main_menu_button_->setText(tr("У ГАЛОЎНАЕ МЕНЮ"));
      break;
    }
  }
}

void GameMenu::ChangeSoundLabel(bool is_enabled, Language language) {
  switch (language) {
    case Language::kEnglish : {
      if(is_enabled) {
        sound_button_->setText(tr("TURN OFF SOUND"));
      } else {
        sound_button_->setText(tr("TURN ON SOUND"));
      }
      break;
    }
    case Language::kRussian : {
      if(is_enabled) {
        sound_button_->setText(tr("ВЫКЛЮЧИТЬ ЗВУК"));
      } else {
        sound_button_->setText(tr("ВКЛЮЧИТЬ ЗВУК"));
      }
      break;
    }
    case Language::kBelarusian : {
      if(is_enabled) {
        sound_button_->setText(tr("ВЫКЛЮЧЫЦЬ ГУК"));
      } else {
        sound_button_->setText(tr("ЎКЛЮЧЫЦЬ ГУК"));
      }
      break;
    }
  }
}
