#include "settings_menu.h"

#include "view/buttons/constants.h"

SettingsMenu::SettingsMenu(AbstractController* controller, QWidget* parent) :
    CustomWidget(controller, parent, ":/menu/screen-options.png"),
    sound_button_(new MenuButton(":/menu/button-sound-on-en.png",
                                 this,
                                 constants::kSound)),
    main_menu_button_(new MenuButton(":/menu/button-main-menu-en.png",
                                     this,
                                     constants::kToMainMenu)),
    russian_(new MenuButton(":/menu/button-language-ru.png", this,
                            constants::kRussian)),
    belarussian_(new MenuButton(":/menu/button-language-by.png", this,
                                constants::kBelarussian)),
    english_(new MenuButton(":/menu/button-language-en.png", this,
                            constants::kEnglish)) {
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
      sound_button_->ChangePixmap(":/menu/button-sound-off-en.png");
      main_menu_button_->ChangePixmap(":/menu/button-main-menu-en.png");
      break;
    }
    case Language::kRussian : {
      sound_button_->ChangePixmap(":/menu/button-sound-off-ru.png");
      main_menu_button_->ChangePixmap(":/menu/button-main-menu-ru.png");
      break;
    }
    case Language::kBelarusian : {
      sound_button_->ChangePixmap(":/menu/button-sound-off-by.png");
      main_menu_button_->ChangePixmap(":/menu/button-main-menu-by.png");
      break;
    }
  }
}

void SettingsMenu::ChangeSoundLabel(bool is_enabled, Language language) {
  switch (language) {
    case Language::kEnglish : {
      if (is_enabled) {
        sound_button_->ChangePixmap(":/menu/button-sound-on-en.png");
      } else {
        sound_button_->ChangePixmap(":/menu/button-sound-off-en.png");
      }
      break;
    }
    case Language::kRussian : {
      if (is_enabled) {
        sound_button_->ChangePixmap(":/menu/button-sound-on-ru.png");
      } else {
        sound_button_->ChangePixmap(":/menu/button-sound-off-ru.png");
      }
      break;
    }
    case Language::kBelarusian : {
      if (is_enabled) {
        sound_button_->ChangePixmap(":/menu/button-sound-on-by.png");
      } else {
        sound_button_->ChangePixmap(":/menu/button-sound-off-by.png");
      }
      break;
    }
  }
}
