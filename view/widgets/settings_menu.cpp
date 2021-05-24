#include "settings_menu.h"

#include "view/buttons/constants.h"

SettingsMenu::SettingsMenu(AbstractController* controller, QWidget* parent) :
    CustomWidget(controller, parent),
    sound_button_(new MenuButton(tr("TURN OFF SOUND"),
                                 this,
                                 constants::kSound)),
    main_menu_button_(new MenuButton(tr("TO MAIN MENU"),
                                     this,
                                     constants::kToMainMenu)),
    russian_(new MenuButton(tr("РУССКИЙ"), this, constants::kRussian)),
    belarussian_(new MenuButton(tr("БЕЛАРУССКАЯ"), this,
                                constants::kBelarussian)),
    english_(new MenuButton(tr("ENGLISH"), this, constants::kEnglish)) {

  connect(sound_button_, &::QPushButton::clicked, this, [&] {
    controller_->ChangeSoundState();
  });

  connect(main_menu_button_, &::QPushButton::clicked, this, [&] {
    controller_->OpenMainMenu();
  });

  connect(russian_, &::QPushButton::clicked, this, [&] {
    controller_->ChangeLanguage(Language::kRussian);
  });

  connect(belarussian_, &::QPushButton::clicked, this, [&] {
    controller_->ChangeLanguage(Language::kBelarusian);
  });

  connect(english_, &::QPushButton::clicked, this, [&] {
    controller_->ChangeLanguage(Language::kEnglish);
  });

}

void SettingsMenu::Resize(QSize size) {
  sound_button_->setGeometry(sound_button_->CalculateActualPos(size));
  main_menu_button_->setGeometry(main_menu_button_->CalculateActualPos(size));
  russian_->setGeometry(russian_->CalculateActualPos(size));
  belarussian_->setGeometry(belarussian_->CalculateActualPos(size));
  english_->setGeometry(english_->CalculateActualPos(size));
}

void SettingsMenu::ChangeLanguage(Language language) {
  switch (language) {
    case Language::kEnglish : {
      sound_button_->setText(tr("TURN OFF SOUND"));
      main_menu_button_->setText(tr("TO MAIN MENU"));
      break;
    }
    case Language::kRussian : {
      sound_button_->setText(tr("ВЫКЛЮЧИТЬ ЗВУК"));
      main_menu_button_->setText(tr("В ГЛАВНОЕ МЕНЮ"));
      break;
    }
    case Language::kBelarusian : {
      sound_button_->setText(tr("ВЫКЛЮЧЫЦЬ ГУК"));
      main_menu_button_->setText(tr("У ГАЛОЎНАЕ МЕНЮ"));
      break;
    }
  }
}

void SettingsMenu::ChangeSoundLabel(bool is_enabled, Language language) {
  switch (language) {
    case Language::kEnglish : {
      if (is_enabled) {
        sound_button_->setText(tr("TURN OFF SOUND"));
      } else {
        sound_button_->setText(tr("TURN ON SOUND"));
      }
      break;
    }
    case Language::kRussian : {
      if (is_enabled) {
        sound_button_->setText(tr("ВЫКЛЮЧИТЬ ЗВУК"));
      } else {
        sound_button_->setText(tr("ВКЛЮЧИТЬ ЗВУК"));
      }
      break;
    }
    case Language::kBelarusian : {
      if (is_enabled) {
        sound_button_->setText(tr("ВЫКЛЮЧЫЦЬ ГУК"));
      } else {
        sound_button_->setText(tr("ЎКЛЮЧЫЦЬ ГУК"));
      }
      break;
    }
  }
}