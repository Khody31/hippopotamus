#include <QKeyEvent>

#include "game_menu.h"
#include "constants.h"

GameMenu::GameMenu(AbstractController* controller,
                   QWidget* parent) :
    CustomWidget(controller, parent),
    resume_button_(new MenuButton(tr("RESUME"),
                                  this,
                                  menu_constants::kResumeButton)),
    sound_button_(new MenuButton(tr("SOUND"),
                                 this,
                                 menu_constants::kSoundButton)),
    to_main_menu_button_(new MenuButton(tr("TO MAIN MENU"),
                                        this,
                                        menu_constants::kToMainMenuButton)) {

  connect(resume_button_, &::QPushButton::clicked, this, [&] {
    controller_->ContinueGame();
  });

  connect(sound_button_, &::QPushButton::clicked, this, [&] {

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
  // ignore event for it to be propagated to parent widget (i.e. Game CustomWidget)
  if (event->key() == Qt::Key_Escape) {
    QWidget::keyPressEvent(event);
  }
  controller_->OnKeyPress(event);
}

void GameMenu::keyReleaseEvent(QKeyEvent* event) {
  controller_->OnKeyRelease(event);
}
